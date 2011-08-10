#ifndef F_SCENES_DUNGEON_H
#define F_SCENES_DUNGEON_H

#include <stuff/map.h>

typedef enum {
	STARTING,
	RUNNING,
	PAUSED,
	HALTING
} F_dungeonStatus;

typedef struct {
	F_dungeonStatus status;
	F_stuff_map map;
} F_dungeon;

static int
F_scenes_dungeon_init();

static int
F_scenes_dungeon_update();

static int
F_scenes_dungeon_halt();

#endif // F_SCENES_DUNGEON_H
