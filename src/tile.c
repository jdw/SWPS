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
	t->traversable = 1;
	
	return 0;
}

int
fTile_update(fTile* t) {
	
	return 0;
}
