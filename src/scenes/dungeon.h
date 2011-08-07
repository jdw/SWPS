#ifndef F_SCENES_DUNGEON_H
#define F_SCENES_DUNGEON_H

#include <stuff/world_map.h>

typedef enum {
	STARTING,
	RUNNING,
	PAUSED,
	STOPING
} F_dungeonStatus;

typedef struct {
	F_dungeonStatus status;
	F_dungeonMap map;
} F_dungeon;

static int
F_scenesDungeon_init();

#endif // F_SCENES_DUNGEON_H
