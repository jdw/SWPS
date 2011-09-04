#ifndef F_MAP_H
#define F_MAP_H

#include "tile.h"

#include <SFML/Graphics.h>

struct sfRenderWindow;

struct fMap {
	int width;
	int height;
	fTile** tiles;
	const int (*draw)(struct fMap* const);
};

typedef struct fMap fMap;

fMap*
fMap_create(const int, const int);

const int
fMap_init(fMap* const);

const int
fMap_update(fMap* const);

const int
fMap_draw(fMap* const);

const int
fMap_setActor(fMap* const m, struct fActor* const a, int x, int y);

const int
fMap_setVisibleArea(fMap* const m, int x, int y, int r);

const int
fMap_getTile(fMap* const m, int x, int y, fTile** t);

#endif // F_MAP_H
