#ifndef F_STUFF_TILE_H
#define F_STUFF_TILE_H

typedef enum {
	WALL,
	DOOR,
	FLOOR,
	STAIRS_DOWN,
	STAIRS_UP
} F_tileType;

typedef struct {
	F_tile* north, east, south, west;
	F_tileType type;
} F_tile;

static int
F_stuff_tile_create();

#endif // F_STUFF_TILE_H
