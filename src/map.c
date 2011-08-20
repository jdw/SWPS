#include "map.h"

#include <stdlib.h>
#include <define.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Graphics/Font.h>


#include "tile.h"

static sfSprite* g_pWall = 0;
static sfSprite* g_pFloor = 0;

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
			if (i == 0 || j == 0 || i == m->height - 1 || j == m->width - 1) m->tiles[i][j].type = WALL;
			else  m->tiles[i][j].type =  FLOOR;

			if (m->tiles[i][j].type == FLOOR && g_pFloor == 0) {
				sfImage* t_pImage = sfImage_CreateFromFile("ass/dirt_floor.png");
				if (!t_pImage) return EXIT_FAILURE;
				g_pFloor = sfSprite_Create();
				sfSprite_SetImage(g_pFloor, t_pImage);
			}
			else if (m->tiles[i][j].type == WALL && g_pWall == 0) {
				sfImage* t_pImage = sfImage_CreateFromFile("ass/wall_stone.png");
				if (!t_pImage) return EXIT_FAILURE;
				g_pWall = sfSprite_Create();
				sfSprite_SetImage(g_pWall, t_pImage);
			}
				
		}
			
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
fMap_draw(fMap* m, sfRenderWindow* i_pApp) {
	for (int i = 0; i < m->height; ++i)
		for (int j = 0; j < m->width; ++j) {
			int t_x, t_y;
			sfSprite* t_s;
			switch (m->tiles[i][j].type) {
				case FLOOR: {
					t_x = j * sfSprite_GetWidth(g_pFloor);
					t_y = i * sfSprite_GetHeight(g_pFloor);
					t_s = g_pFloor;
				} break;
				case WALL: {
					t_x = j * sfSprite_GetWidth(g_pFloor);
					t_y = i * sfSprite_GetHeight(g_pFloor);
					t_s = g_pWall;
				} break;
			}

			sfSprite_SetPosition(t_s, t_x, t_y);
			sfRenderWindow_DrawSprite(i_pApp, t_s);
				
		}	
	
	return 0;
}
