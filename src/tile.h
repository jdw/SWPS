#ifndef F_STUFF_TILE_H
#define F_STUFF_TILE_H

// Types of tiles
enum fTile_type {
	WALL,
	DOOR,
	FLOOR
};
typedef enum fTile_type fTile_type;

struct fTile {
	fTile_type type;
	int lastSeen; // 0 = never, 1 = just now, > 1 some time ago
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

int
fTile_setActor(fTile*, struct fActor*);

struct fActor*
fTile_getActor(fTile*);

int
fTile_removeActor(fTile*);

#endif // F_TILE_H
