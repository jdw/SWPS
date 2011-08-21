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

// Reason why the tile is blocked
typedef enum {
	ITEM,
	CHARACTER,
	TILE_TYPE
} fTile_blocked;

typedef struct fTile {
	fTile_type type;
	int found;
	int lastSeen;
	struct fCharacter* chars;
	struct fItem* items;
} fTile;

fTile*
fTile_create();

int fTile_reset(fTile* t);

int
fTile_update(fTile* t);

int
fTile_isBlocked(fTile*);


#endif // F_TILE_H
