#include <tile.h>

#include <stdlib.h>

F_tile*
F_stuff_tile_create() {
	F_tile* t_ret = (F_tile*) malloc(sizeof(F_tile));
	t_ret->neighbors = (F_tile**) malloc(4 * sizeof(F_tile*));
	t_ret->neighbors[0] = (F_tile*)0;
	t_ret->neighbors[1] = (F_tile*)1;
	t_ret->neighbors[2] = (F_tile*)2;
	t_ret->neighbors[3] = (F_tile*)3;

	t_ret->type = MAX;
	return t_ret;
}
