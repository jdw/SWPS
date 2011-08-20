#ifndef F_MAP_H
#define F_MAP_H

#include "tile.h"

struct sfRenderWindow;
#include <SFML/Graphics.h>

/*
typedef enum {
	STARTING,
	RUNNING,
	PAUSED,
	HALTING
} F_dungeonStatus;
*/


typedef struct {
	// ??? F_dungeonStatus status;
	int width;
	int height;
	fTile** tiles;
	// exits**
	// ??? filename
} fMap;

fMap*
fMap_create(const int, const int);

int
fMap_init(fMap*);

int
fMap_update(fMap*);

int
fMap_draw(fMap* t, sfRenderWindow* i_pApp);

#endif // F_MAP_H
