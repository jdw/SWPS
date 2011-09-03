#include <define.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Graphics/Font.h>

#include "ui.h"
#include "map.h"
#include "actor.h"
#include "scene.h"

static sfFont* g_debugFont = 0;
static sfWindowSettings WINDOW_SETTINGS = {24, 8, 0}; 
static sfVideoMode VIDEO_MODE = {800, 600, 32};
static sfRenderWindow* APP = 0;
static fUI* g_pUI;
static int QUIT = 0;

// Graphics
static sfSprite* g_pWall = 0;
static sfSprite* g_pFloor = 0;
static sfSprite* g_pPlayer = 0;
static sfSprite* g_pNPC = 0;

// Actors
static fActor* PLAYER = 0;

int
init() {
	// Create the main window
	APP = sfRenderWindow_Create(VIDEO_MODE, "SWPS", sfResize | sfClose, WINDOW_SETTINGS);
	if (!APP) return EXIT_FAILURE;

	// Loading debug font
	g_debugFont = sfFont_CreateFromFile("ass/FreeSerif.ttf", 50, NULL);
	if (!g_debugFont) return FAILED_LOADING_FONT_FILE;

	// Loading graphics
	sfImage* t_pImage = sfImage_CreateFromFile("ass/dirt_floor.png");
	if (!t_pImage) return FAILED_LOADING_FLOOR_GRAPHICS;
	g_pFloor = sfSprite_Create();
	sfSprite_SetImage(g_pFloor, t_pImage);
	
	t_pImage = sfImage_CreateFromFile("ass/wall_stone.png");
	if (!t_pImage) return FAILED_LOADING_WALL_GRAPHICS;
	g_pWall = sfSprite_Create();
	sfSprite_SetImage(g_pWall, t_pImage);

	// Player and NPC
	t_pImage = sfImage_CreateFromFile("ass/hero.png");
	if (!t_pImage) return EXIT_FAILURE;
	g_pPlayer = sfSprite_Create();
	sfSprite_SetImage(g_pPlayer, t_pImage);

	t_pImage = sfImage_CreateFromFile("ass/enemah.png");
	if (!t_pImage) return EXIT_FAILURE;
	g_pNPC = sfSprite_Create();
	sfSprite_SetImage(g_pNPC, t_pImage);

		
	return AOK;
}
/*
typedef enum {
	MAP,
	STUFF = 1000,
	NPC = 2000,
	PLAYER = 3000,
	EFFECTS = 4000,
	UI = 5000
} F_gfxLayers;
*/
int
scene_setup(fScene* s) {
	fMap* t_m= fMap_create(10, 10);
	fMap_init(t_m);
	s->map = t_m;
	
	PLAYER = fActor_create();
	PLAYER->x = PLAYER->y = 2;
	int t_ret =	fMap_setActor(t_m, PLAYER, 2,2);
	if (t_ret) printf("Nope, actor not set to map, error: %d\n", t_ret);

	printf("Scene inited!\n");
	s->state = UPDATE;
	
	return AOK;
}

int
scene_update(fScene* s) {
	fMap_update(s->map);

	fMap_setVisibleArea(s->map, PLAYER->x, PLAYER->y, 2);

	return AOK;
}

int
scene_draw(fScene* s) {
	// Map
	fMap* m = s->map;
	for (int x = 0; x < m->width; ++x)
		for (int y = 0; y < m->height; ++y) {
			fTile* t = &m->tiles[x][y];
			if (t->lastSeen != 1) continue;
			
			int t_x, t_y;
			sfSprite* t_s;

			switch (m->tiles[x][y].type) {
				case FLOOR: {
					t_x = x * sfSprite_GetWidth(g_pFloor);
					t_y = y * sfSprite_GetHeight(g_pFloor);
					t_s = g_pFloor;
				} break;
				case WALL: {
					t_x = x * sfSprite_GetWidth(g_pFloor);
					t_y = y * sfSprite_GetHeight(g_pFloor);
					t_s = g_pWall;
				} break;
			}

			sfSprite_SetPosition(t_s, t_x, t_y);
			sfRenderWindow_DrawSprite(APP, t_s);
			
			if (m->tiles[x][y].actor) {
				sfSprite_SetPosition(g_pPlayer, t_x, t_y);
				sfRenderWindow_DrawSprite(APP, g_pPlayer);
			}
							
		}
}

int
scene_input(fScene* s) {
	sfEvent t_event;
	int t_x = PLAYER->x, t_y = PLAYER->y; // Players new pos
	char *t_pMsg = 0;
	int t_playerMoved = 0;

	while (sfRenderWindow_GetEvent(APP, &t_event)) {
		if (t_event.Type == sfEvtKeyPressed) {
			switch (t_event.Key.Code) {
				case sfKeyEscape: s->state = DONE; break;
				case sfKeyUp:
				case sfKeyNumpad8: {
					t_x -=  0; t_y -= 1;
					t_pMsg = "Hero moves up!";
					t_playerMoved++;
				} break;
				
				case sfKeyRight:
				case sfKeyNumpad6: {
					t_x += 1; t_y += 0;
					t_pMsg = "Hero moves right!";
					t_playerMoved++;
				} break;
				
				case sfKeyDown:
				case sfKeyNumpad2: {
					t_x -= 0; t_y += 1;
					t_pMsg = "Hero moves down!";
					t_playerMoved++;
				} break;
				
				case sfKeyLeft:
				case sfKeyNumpad4: {
					t_x -= 1; t_y -= 0;
					t_pMsg = "Hero moves left!";
					t_playerMoved++;
				} break;
				
				default: break;
			}
		}
	}

	if (t_playerMoved) {
		int t_ret = fMap_setActor(s->map, PLAYER, t_x, t_y);
		if (t_ret == TILE_BLOCKED_ITEM) t_pMsg = "There is an item in the way!";
	    if (t_ret == TILE_BLOCKED_ACTOR) t_pMsg = "There is an actor in the way!";
	    if (t_ret == TILE_BLOCKED_TYPE) t_pMsg = "That path is blocked!";
				
		fUI_setMessage(g_pUI, t_pMsg);
	}

	return AOK;
}

int
main() {
	int t_initReturn;
	if ((t_initReturn = init())) {
		printf("init() failed with code: %d\n", t_initReturn);
		return t_initReturn;
	}

	g_pUI = fUI_create();

	fScene* t_s = fScene_create();
	t_s->setup = scene_setup;
	t_s->update = scene_update;
	t_s->draw = scene_draw;
	t_s->input = scene_input;

	// Start the game loop
	while (t_s->state != DONE) {
		fUI_update(g_pUI); // Update UI
		fScene_update(t_s); // Update scene
		
		fScene_input(t_s);

		sfRenderWindow_Clear(APP, sfBlack); // Clear the screen
		fScene_draw(t_s); // Draw the scene
		fUI_draw(g_pUI, APP); // Draw UI
		sfRenderWindow_Display(APP); // Update window
	}

	sfRenderWindow_Close(APP); // Close app
	// Cleanup resources
	sfRenderWindow_Destroy(APP);
 
	return EXIT_SUCCESS;
}
