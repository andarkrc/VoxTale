#include <string.h>

#include "data_structures.h"
#include "error.h"

list_t *list_create(void (*data_destroy)(void *))
{
	list_t *list = malloc(sizeof(*list));
	ASSERT(list, ERR_MEM_FAIL);
	list->size = 0;
	list->head = list->tail = NULL;
	list->data_destroy = data_destroy;
	return list;
}

void list_add(list_t *list, size_t index, void *data)
{
	list_node_t *node = malloc(sizeof(*node));
	ASSERT(node, ERR_MEM_FAIL);
	node->data = data;
	if (index > list->size)
	{
		index = list->size;
	}
	if (list->size == 0)
	{
		node->next = node->prev = NULL;
		list->head = list->tail = node;
		list->size++;
		return;
	}
	if (index == 0)
	{
		node->next = list->head;
		node->prev = NULL;
		list->head->prev = node;
		list->head = node;
		list->size++;
		return;
	}

	list_node_t *current = list->head;
	index--;
	for (; index; current = current->next, index--);

	node->prev = current;
	node->next = current->next;

	if (node->next == NULL)
	{
		list->tail = node;
	}
	current->next = node;
	list->size++;
}

void *list_get(list_t *list, size_t index)
{
	if (index >= list->size)
	{
		return NULL;
	}
	list_node_t *current = list->head;
	for (; index; current = current->next, index--);
	return current->data;
}

void *list_remove(list_t *list, size_t index)
{
	if (index >= list->size)
	{
		return NULL;
	}
	void *data;
	if (list->size == 1)
	{
		data = list->head->data;
		free(list->head);
		list->head = list->tail = NULL;
		list->size--;
		return data; 
	}
	if (index == 0)
	{
		data = list->head->data;
		list_node_t *node = list->head;
		list->head->next->prev = NULL;
		list->head = node->next;
		free(node);
		list->size--;
		return data;
	}
	list_node_t *current = list->head;
	for (; index; current = current->next, index--);
	current->prev->next = current->next;
	if (current->next)
	{
		current->next->prev = current->prev;
	}
	else
	{
		list->tail = current->prev;
	}
	data = current->data;
	free(current);
	list->size--;
	return data;
}

void list_destroy(list_t *list)
{
	while (list->size > 0)
	{
		void *data = list_remove(list, 0);
		if (list->data_destroy)
		{
			list->data_destroy(data);
		}
	}
	free(list);
}

static size_t hash_string(char *key)
{
	unsigned char *key_string = (unsigned char *)key;
	size_t hash = 5381;
	int c;

	while ((c = *key_string++))
		hash = ((hash << 5u) + hash) + c;

	return hash;
}

hashmap_t *hashmap_create(void (*data_destroy)(void*))
{
	hashmap_t *map = malloc(sizeof(*map));
	ASSERT(map, ERR_MEM_FAIL);
	map->capacity = 100;
	map->size = 0;
	map->data_destroy = data_destroy;
	map->buckets = calloc(100, sizeof(*map->buckets));
	ASSERT(map->buckets, ERR_MEM_FAIL);

	return map;
}

void hashmap_put(hashmap_t *map, char *key, void *data)
{
	size_t index = hash_string(key) % map->capacity;

	entry_t *old_entry = map->buckets[index];
	while (old_entry)
	{
		if (strcmp(old_entry->key, key) == 0)
		{
			break;
		}
		old_entry = old_entry->next;
	}

	if (!old_entry)
	{
		entry_t *entry = malloc(sizeof(*entry));
		ASSERT(entry, ERR_MEM_FAIL);

		entry->next = map->buckets[index];
		map->buckets[index] = entry;

		entry->key = malloc(strlen(key) + 1);
		ASSERT(entry->key, ERR_MEM_FAIL);
		strcpy(entry->key, key);
		entry->data = data;
		map->size++;
	}
	else
	{
		old_entry->data = data;
	}
}

void *hashmap_get(hashmap_t *map, char *key)
{
	size_t index = hash_string(key) % map->capacity;

	entry_t *entry = map->buckets[index];
	while (entry)
	{
		if (strcmp(entry->key, key) == 0)
		{
			return entry->data;
		}
		entry = entry->next;
	}

	return NULL;
}

void *hashmap_remove(hashmap_t *map, char *key)
{
	size_t index = hash_string(key) % map->capacity;

	entry_t *prev = NULL;
	entry_t *entry = map->buckets[index];
	while (entry)
	{
		if (strcmp(entry->key, key) == 0)
		{
			if (prev == NULL)
			{
				map->buckets[index] = entry->next;
			}
			else
			{
				prev->next = entry->next;
			}
			free(entry->key);
			void *data = entry->data;
			free(entry);
			return data;
		}
		prev = entry;
		entry = entry->next;
	}

	return NULL;
}

void hashmap_destroy(hashmap_t *map)
{
	for (size_t i = 0; i < map->capacity; i++)
	{
		while (map->buckets[i])
		{
			entry_t *entry = map->buckets[i];
			map->buckets[i] = entry->next;

			free(entry->key);
			if (map->data_destroy)
			{
				map->data_destroy(entry->data);
			}
			free(entry);
		}
	}
	free(map->buckets);
	free(map);
}