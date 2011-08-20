#include "map.h"

#include <stdlib.h>
#include <define.h>

#include "tile.h"

fMap*
fMap_create(const int h, const int w) {
	fMap* t_ret = (fMap*) malloc(sizeof(fMap));

	t_ret->tiles = (fTile*) malloc(h * sizeof(fTile*));
	for (int i = 0; i < h; ++i)
		t_ret->tiles[i] = (fTile*) malloc(w * sizeof(fTile));
	
	t_ret->height = h;
	t_ret->width = w;

	return t_ret;
}

int
fMap_init(fMap* m) {
	return 0;
}

int
fMap_update(fMap* m) {
	for (int i = 0; i < m->height; ++i)
		for (int j = 0; j < m->width; ++j)
			fTile_update(&m->tiles[i][j]);
	
	return 0;
}

int
fMap_halt(fMap* m) {
	return 0;

}
