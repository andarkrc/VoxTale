#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <stdlib.h>

struct list_node_t {
	struct list_node_t *next;
	struct list_node_t *prev;
	void *data;
};

typedef struct list_node_t list_node_t;

typedef struct
{
	list_node_t *head;
	list_node_t *tail;
	size_t size;
	void (*data_destroy)(void *);
} list_t;

struct entry_t
{
	struct entry_t *next;
	void *data;
	char *key;
};

typedef struct entry_t entry_t;

typedef struct
{
	entry_t **buckets;
	size_t capacity;
	size_t size;
	void (*data_destroy)(void *);
} hashmap_t;

list_t *list_create(void (*data_destroy)(void *));
void list_destroy(list_t *list);
void list_add(list_t *list, size_t index, void *data);
void *list_get(list_t *list, size_t index);
void *list_remove(list_t *list, size_t index);

#define list_push(list, data) list_add((list), list->size, (data))

hashmap_t *hashmap_create(void (*data_destroy)(void *));
void *hashmap_get(hashmap_t *map, char *key);
void hashmap_put(hashmap_t *map, char *key, void *data);
void *hashmap_remove(hashmap_t *map, char *key);
void hashmap_destroy(hashmap_t *map);

#define hashmap_add(map, key, data) hashmap_put((map), (key), (data))
#define map_create(data_destroy) hashmap_create((data_destroy))
#define map_add(map, key, data) hashmap_put((map), (key), (data))
#define map_put(map, key, data) hashmap_put((map), (key), (data))
#define map_get(map, key) hashmap_get((map), (key))
#define map_remove(map, key) hashmap_remove((map), (key))
#define map_destroy(map) hashmap_destroy((map))

#endif
