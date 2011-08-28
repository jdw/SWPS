#include "map.h"

#include <stdlib.h>
#include <define.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Graphics/Font.h>


#include "actor.h"
#include "tile.h"

static sfSprite* g_pWall = 0;
static sfSprite* g_pFloor = 0;
static sfSprite* g_pPlayer = 0;
static sfSprite* g_pNPC = 0;

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
	
	// Player and NPC
	sfImage* t_pImage = sfImage_CreateFromFile("ass/hero.png");
	if (!t_pImage) return EXIT_FAILURE;
	g_pPlayer = sfSprite_Create();
	sfSprite_SetImage(g_pPlayer, t_pImage);

	t_pImage = sfImage_CreateFromFile("ass/enemah.png");
	if (!t_pImage) return EXIT_FAILURE;
	g_pNPC = sfSprite_Create();
	sfSprite_SetImage(g_pNPC, t_pImage);

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
			
			if (m->tiles[i][j].actor) {
				sfSprite_SetPosition(g_pPlayer, t_x, t_y);
				sfRenderWindow_DrawSprite(i_pApp, g_pPlayer);
			}
							
		}	
	
	return 0;
}

int
fMap_setActor(fMap* m, fActor* a, int x, int y) {	
	if (!(0 <= x && x < m->width)) return MAP_POS_X_OUTSIDE;
	if (!(0 <= y && y < m->height)) return MAP_POS_Y_OUTSIDE;
	
	return fTile_setActor(&m->tiles[x][y], a);
}

/*
int
fMap_setItem(fMap* m, fItem* i, int x, int y) {

}
*/
