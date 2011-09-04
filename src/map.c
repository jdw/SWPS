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

const int
fMap_init(fMap* const m) {
	for (int i = 0; i < m->height; ++i)
		for (int j = 0; j < m->width; ++j) {
			fTile_reset(&m->tiles[i][j]);

			if ((i == 0 || j == 0 || i == m->height - 1 || j == m->width - 1) ||
				(i == 10 && j < 5))  m->tiles[i][j].type = WALL;
			else  m->tiles[i][j].type =  FLOOR;
		}
	
	return AOK;
}

const int
fMap_update(fMap* const m) {
	for (int x = 0; x < m->width; ++x)
		for (int y = 0; y < m->height; ++y)
			fTile_update(&m->tiles[x][y]);
	
	return AOK;
}

const int
fMap_draw(fMap* const m) {
	if (m->draw) return m->draw(m);		
	return AOK;
}

const int
fMap_setActor(fMap* const m, fActor* const a, int x, int y) {	
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

const int
fMap_getTile(fMap* const m, int x, int y, fTile** t) {
	if (!(0 <= x && x < m->width)) return MAP_POS_X_OUTSIDE;
	if (!(0 <= y && y < m->height)) return MAP_POS_Y_OUTSIDE;
	
	*t = &m->tiles[x][y];

	return AOK;
}

const int
fMap_setVisibleArea(fMap* const m, int x, int y, int r) {
	for (int i = x - r; i <= x + r; i++) {
		for (int j = y - r; j <= y + r; j++) {
			if (!(i == x - r || i == x + r || j == y - r || j == y + r)) continue;
			// Inside frame of light
			if (x == i) { // Line is vertical
				if (j < y) {
					for (int y2 = y; y2 >= j; y2--) {
						fTile* t = 0;
						fMap_getTile(m, i, y2, &t);	
						if (t) {
							t->lastSeen = 1;
							if (t->type == WALL) break;
						}
					}
				}
				else {
					for (int y2 = y; y2 <= j; y2++) {
						fTile* t = 0;
						fMap_getTile(m, i, y2, &t);	
						if (t) {
							t->lastSeen = 1;
							if (t->type == WALL) break;
						}
					}
				}
			}
			else if (y == j) { // Line is horizontal
				if (i < x) {
					for (int x2 = x; x2 >= i; x2--) {
						fTile* t = 0;
						fMap_getTile(m, x2, j, &t);	
						if (t) {
							t->lastSeen = 1;
							if (t->type == WALL) break;
						}
					}
				}
				else {
					for (int x2 = x; x2 <= i; x2++) {
						fTile* t = 0;
						fMap_getTile(m, x2, j, &t);	
						if (t) {
							t->lastSeen = 1;
							if (t->type == WALL) break;
						}
					}
				}
			}
			else { // Line's not straight
				int x1 = i, x0 = x;
				int y1 = j, y0 = y;
				int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
				int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
				int err = (dx>dy ? dx : -dy)/2, e2;

				while (1) {
					fTile* t = 0;
					fMap_getTile(m, x0, y0, &t);
					if (t) {
						t->lastSeen = 1;
						if (t->type == WALL) break;
					}
					
					if (x0==x1 && y0==y1) break;
					e2 = err;
					if (e2 >-dx) { err -= dy; x0 += sx; }
					if (e2 < dy) { err += dx; y0 += sy; }
				}
			}
		}
	}

	return AOK;
}
/*
			}



function line(x0, x1, y0, y1)
     int deltax := x1 - x0
     int deltay := y1 - y0
     real error := 0
     real deltaerr := abs (deltay / deltax)    // Assume deltax != 0 (line is not vertical),
           // note that this division needs to be done in a way that preserves the fractional part
     int y := y0
     for x from x0 to x1
         plot(x,y)
         error := error + deltaerr
         if error ≥ 0.5 then
             y := y + 1
             error := error - 1.0
*/
/*
int
fMap_setItem(fMap* m, fItem* i, int x, int y) {

}
*/
