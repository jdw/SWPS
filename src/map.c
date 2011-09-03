#include "map.h"

#include <stdlib.h>
#include <define.h>
#include <stdio.h>


#include "actor.h"
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
	for (int i = 0; i < m->height; ++i)
		for (int j = 0; j < m->width; ++j) {
			fTile_reset(&m->tiles[i][j]);

			if (i == 0 || j == 0 || i == m->height - 1 || j == m->width - 1) m->tiles[i][j].type = WALL;
			else  m->tiles[i][j].type =  FLOOR;
		}
	
	return AOK;
}

int
fMap_update(fMap* m) {
	for (int x = 0; x < m->width; ++x)
		for (int y = 0; y < m->height; ++y)
			fTile_update(&m->tiles[x][y]);
	
	return AOK;
}

int
fMap_draw(fMap* m, sfRenderWindow* i_pApp) {
			
	return AOK;
}

int
fMap_setActor(fMap* m, fActor* a, int x, int y) {	
	if (!(0 <= x && x < m->width)) return MAP_POS_X_OUTSIDE;
	if (!(0 <= y && y < m->height)) return MAP_POS_Y_OUTSIDE;
	
	int t_ret = fTile_setActor(&m->tiles[x][y], a);
	if (t_ret) return t_ret; // Something went wrong
	else {
		fTile_removeActor(&m->tiles[a->x][a->y]);
		a->x = x;
		a->y = y;
	}

	return AOK;
}

int
fMap_getTile(fMap* m, int x, int y, fTile** t) {
	if (!(0 <= x && x < m->width)) return MAP_POS_X_OUTSIDE;
	if (!(0 <= y && y < m->height)) return MAP_POS_Y_OUTSIDE;
	
	*t = &m->tiles[x][y];

	return AOK;
}

int
fMap_setVisibleArea(fMap* m, int x, int y, int r) {
	for (int i = x - r; i <= x + r; i++)
		for (int j = y - r; j <= y + r; j++) {
			fTile* t = 0;
			fMap_getTile(m, i, j, &t);

			if (t) {
				t->lastSeen = 1;
			}
		}

	return AOK;
}
/*
int
fMap_setItem(fMap* m, fItem* i, int x, int y) {

}
*/
