#ifndef F_STUFF_TILE_H
#define F_STUFF_TILE_H

typedef enum {
	WALL,
	DOOR,
	FLOOR,
	STAIRS,

	MAX
} fTile_type;

typedef struct fTile {
	fTile_type type;
	int found;
	int lastSeen;
	int traversable;
} fTile;

fTile*
fTile_create();

int fTile_reset(fTile* t);

int
fTile_update(fTile* t);

#endif // F_TILE_H
