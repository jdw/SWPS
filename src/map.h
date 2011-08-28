#ifndef F_MAP_H
#define F_MAP_H

#include "tile.h"

#include <SFML/Graphics.h>

struct sfRenderWindow;
typedef struct fActor fActor;

/*
typedef enum {
	STARTING,
	RUNNING,
	PAUSED,
	HALTING
} F_dungeonStatus;
*/


struct fMap {
	// ??? F_dungeonStatus status;
	int width;
	int height;
	fTile** tiles;
	// exits**
	// ??? filename
};

typedef struct fMap fMap;

fMap*
fMap_create(const int, const int);

int
fMap_init(fMap*);

int
fMap_update(fMap*);

int
fMap_draw(fMap*, sfRenderWindow* i_pApp);

int
fMap_setActor(fMap* m, fActor* a, int x, int y);

#endif // F_MAP_H
