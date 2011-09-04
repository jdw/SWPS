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
static int INPUTED = 0;

// Graphics
static sfSprite* g_pWall = 0;
static sfSprite* g_pFloor = 0;
static sfSprite* g_pDoor = 0;
static sfSprite* g_pPlayer = 0;
static sfSprite* g_pNPC = 0;
static sfSprite* g_pHalfseen = 0;

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
	
	t_pImage = sfImage_CreateFromFile("ass/halfseen.png");
	if (!t_pImage) return FAILED_LOADING_HALFSEEN_GRAPHICS;
	g_pHalfseen = sfSprite_Create();
	sfSprite_SetImage(g_pHalfseen, t_pImage);

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
	fMap* t_m= fMap_create(50, 50);
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

	fMap_setVisibleArea(s->map, PLAYER->x, PLAYER->y, 5);

	return AOK;
}

int
scene_draw(fScene* s) {
	// Map
	fMap* m = s->map;
	int t_offX = -(PLAYER->x * 16) + 800 / 2;
	int t_offY = -(PLAYER->y * 16) + 200;

	for (int x = 0; x < m->width; ++x)
		for (int y = 0; y < m->height; ++y) {
			fTile* t = &m->tiles[x][y];
			if (!t->lastSeen) continue;
			int t_x, t_y;
			sfSprite* t_s;

			switch (t->type) {
				case FLOOR: {
					t_x = t_offX + x * sfSprite_GetWidth(g_pFloor);
					t_y = t_offY + y * sfSprite_GetHeight(g_pFloor);
					t_s = g_pFloor;
				} break;
				case WALL: {
					t_x = t_offX + x * sfSprite_GetWidth(g_pFloor);
					t_y = t_offY + y * sfSprite_GetHeight(g_pFloor);
					t_s = g_pWall;
				} break;
			}

			sfSprite_SetPosition(t_s, t_x, t_y);
			sfRenderWindow_DrawSprite(APP, t_s);
			
			if (t->lastSeen > 1) {
				sfSprite_SetPosition(g_pHalfseen, t_x, t_y);
				sfRenderWindow_DrawSprite(APP, g_pHalfseen);
			}

			if (t->actor) {
				sfSprite_SetPosition(g_pPlayer, t_x, t_y);
				sfRenderWindow_DrawSprite(APP, g_pPlayer);
			}
							
		}

	return AOK;
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
		
		INPUTED = 1;				
		fUI_setMessage(g_pUI, t_pMsg);
	}

	return AOK;
}

const int
ui_draw(fUI* const u) {
	
	int t_value = 0;
	char* t_string;

	for (int i = 0; i < 2; i++) { 
		t_value = 10 * u->pInfos[i].fValue;
		switch(t_value) {
			case 0: t_string = "[          ]\0"; break;
			case 1: t_string = "[|         ]\0"; break;
			case 2: t_string = "[||        ]\0"; break;
			case 3: t_string = "[|||       ]\0"; break;
			case 4: t_string = "[||||      ]\0"; break;
			case 5: t_string = "[|||||     ]\0"; break;
			case 6: t_string = "[||||||    ]\0"; break;
			case 7: t_string = "[|||||||   ]\0"; break;
			case 8: t_string = "[||||||||  ]\0"; break;
			case 9: t_string = "[||||||||| ]\0"; break;
			default: t_string = "[||||||||||]\0"; break;
		
		}

		const int BUFFER_SIZE = 100;
		char buf[BUFFER_SIZE];
		const char* t = &buf;
		snprintf(t, BUFFER_SIZE, "%s: %s", u->pInfos[i].pKey, t_string);
		sfString_SetText(u->pText, t);
		sfString_SetPosition(u->pText, 700, 550 - i * 20);
		sfRenderWindow_DrawString(APP, u->pText);

	}

	// Printing messages
	for (int i = 0; i < MESSAGE_ROWS; i++) {
		sfString_SetText(u->pText, u->pMessages[i]);
		sfString_SetPosition(u->pText, 10, 550 - i * 20);
		sfRenderWindow_DrawString(APP, u->pText);
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
	fUI_reset(g_pUI);
	g_pUI->draw = ui_draw;
	g_pUI->pText = sfString_Create();
	sfString_SetSize(g_pUI->pText, 15);
	sfString_SetFont(g_pUI->pText, sfFont_GetDefaultFont());


	fScene* t_s = fScene_create();
	fScene_reset(t_s);
	t_s->setup = scene_setup;
	t_s->update = scene_update;
	t_s->draw = scene_draw;
	t_s->input = scene_input;
	fScene_setup(t_s);

	// Start the game loop
	while (t_s->state != DONE) {
		fScene_input(t_s);
		
		if (!INPUTED) continue;
		INPUTED = 0;

		fUI_update(g_pUI); // Update UI
		fScene_update(t_s); // Update scene
		
		sfRenderWindow_Clear(APP, sfBlack); // Clear the screen
		fScene_draw(t_s); // Draw the scene
		fUI_draw(g_pUI); // Draw UI
		sfRenderWindow_Display(APP); // Update window
	}

	sfRenderWindow_Close(APP); // Close app
	// Cleanup resources
	sfRenderWindow_Destroy(APP);
 
	return EXIT_SUCCESS;
}
