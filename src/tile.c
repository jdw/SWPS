#include "tile.h"

#include <stdlib.h>

#include "define.h"
#include "actor.h"

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

int
fTile_isBlocked(fTile* t) {
	if (t->type == WALL) return TILE_BLOCKED_TYPE;
	if (t->actor) return TILE_BLOCKED_ACTOR;
	if (t->items) return TILE_BLOCKED_ITEM;

	return 0; // Nothing is in the way
}

int
fTile_setActor(fTile* t, fActor* a) {
	int t_ret = fTile_isBlocked(t);

	if (t_ret) return t_ret;

	t->actor = a;

	return AOK;
}

fActor*
fTile_getActor(fTile* t) { return t->actor; }

int
fTile_removeActor(fTile* t) {
	t->actor = 0;

	return AOK;
}
