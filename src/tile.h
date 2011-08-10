#ifndef F_STUFF_TILE_H
#define F_STUFF_TILE_H

typedef enum {
	WALL,
	DOOR,
	FLOOR,
	STAIRS_DOWN,
	STAIRS_UP,

	MAX
} F_tileType;

typedef struct F_tile {
	struct F_tile** neighbors;
	F_tileType type;
} F_tile;

F_tile*
F_stuff_tile_create();

#endif // F_STUFF_TILE_H
