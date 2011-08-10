#ifndef F_STUFF_MAP_H
#define F_STUFF_MAP_H

#include <stuff/map.h>

/*
typedef enum {
        STARTING,
        RUNNING,
        PAUSED,
        HALTING
} F_dungeonStatus;
*/
typedef struct {
        F_dungeonStatus status;
        int width;
	int height;
	
} F_map;

static int
F_stuff_map_init(F_map*);

static int
F_stuff_map_update(F_map*);

static int
F_stuff_map_halt(F_map*);

#endif // F_STUFF_MAP_H
