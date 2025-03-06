#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "voxel.h"

voxel_model *default_voxel = NULL;

voxel_model *voxel_get_default(void)
{
	if (default_voxel != NULL)
	{
		return default_voxel;
	}

	default_voxel = malloc(sizeof(*default_voxel));
	ASSERT(default_voxel, ERR_MEM_FAIL);

	default_voxel->face0 = model_load_from_obj("./assets/models/cube_face1.obj", "cube_face1");
	default_voxel->face1 = model_load_from_obj("./assets/models/cube_face2.obj", "cube_face2");
	default_voxel->face2 = model_load_from_obj("./assets/models/cube_face3.obj", "cube_face3");
	default_voxel->face3 = model_load_from_obj("./assets/models/cube_face4.obj", "cube_face4");
	default_voxel->face4 = model_load_from_obj("./assets/models/cube_face5.obj", "cube_face5");
	default_voxel->face5 = model_load_from_obj("./assets/models/cube_face6.obj", "cube_face6");
	
	default_voxel->face[0] = default_voxel->face0;
	default_voxel->face[1] = default_voxel->face1;
	default_voxel->face[2] = default_voxel->face2;
	default_voxel->face[3] = default_voxel->face3;
	default_voxel->face[4] = default_voxel->face4;
	default_voxel->face[5] = default_voxel->face5;


	return default_voxel;
}