#ifndef F_MAP_H
#define F_MAP_H

#include "tile.h"

#include <SFML/Graphics.h>

struct sfRenderWindow;

struct fMap {
	int width;
	int height;
	fTile** tiles;
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
fMap_setActor(fMap* m, struct fActor* a, int x, int y);

int
fMap_setVisibleArea(fMap* m, int x, int y, int r);

int
fMap_getTile(fMap* m, int x, int y, fTile** t);

#endif // F_MAP_H
