#ifndef F_STUFF_TILE_H
#define F_STUFF_TILE_H

// Types of tiles
typedef enum {
	WALL,
	DOOR,
	FLOOR,
	STAIRS,

	MAX
} fTile_type;

struct fTile {
	fTile_type type;
	int found;
	int lastSeen;
	struct fActor* actor;
	struct fItem* items;
};

typedef struct fTile fTile;

fTile*
fTile_create();

int
fTile_reset(fTile* t);

int
fTile_update(fTile* t);

int
fTile_isBlocked(fTile*);

#endif // F_TILE_H
