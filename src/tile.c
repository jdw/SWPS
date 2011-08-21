#include "tile.h"

#include <stdlib.h>

fTile*
fTile_create() {
	fTile* t_ret = (fTile*) malloc(sizeof(fTile));

	fTile_reset(t_ret);
	return t_ret;
}

int
fTile_reset(fTile* t) {
	t->found = 0;
	t->lastSeen = 0;
	
	return 0;
}

int
fTile_update(fTile* t) {
	
	return 0;
}

int fTile_isBlocked(fTile* t) {
	if (t->type == WALL) return TILE_TYPE;
	if (t->chars) return CHARACTER;
	if (t->items) return ITEM;

	return 0; // Nothing is in the way
}
