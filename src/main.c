#include <define.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Graphics/Font.h>

#include "ui.h"

static sfFont* g_debugFont = 0;
static sfWindowSettings WINDOW_SETTINGS = {24, 8, 0}; 
static sfVideoMode VIDEO_MODE = {800, 600, 32};
static sfRenderWindow* APP = 0;
static sfSprite* g_pWall;
static sfSprite* g_pFloor;
static sfSprite* g_pPlayer;
static sfSprite* g_pNPC;
static F_UI* g_pUI;

static int
init() {
	// Create the main window
	APP = sfRenderWindow_Create(VIDEO_MODE, "SWPS", sfResize | sfClose, WINDOW_SETTINGS);
	if (!APP) return EXIT_FAILURE;

	// Loading debug font
	g_debugFont = sfFont_CreateFromFile("ass/FreeSerif.ttf", 50, NULL);
	if (!g_debugFont) return FAILED_LOADING_FONT_FILE;

	// Wall and floor graphics
	sfImage* t_pImage = sfImage_CreateFromFile("ass/wall_stone.png");
	if (!t_pImage) return EXIT_FAILURE;
	g_pWall = sfSprite_Create();
	sfSprite_SetImage(g_pWall, t_pImage);

	t_pImage = sfImage_CreateFromFile("ass/dirt_floor.png");
	if (!t_pImage) return EXIT_FAILURE;
	g_pFloor = sfSprite_Create();
	sfSprite_SetImage(g_pFloor, t_pImage);
	
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

typedef enum {
	MAP,
	STUFF = 1000,
	NPC = 2000,
	PLAYER = 3000,
	EFFECTS = 4000,
	UI = 5000
} F_gfxLayers;

static int
F_draw(F_gfxLayers i_layer, sfSprite* i_pAsset, const int i_x, const int i_y) {

	sfSprite_SetPosition(i_pAsset, i_x, i_y);
	sfRenderWindow_DrawSprite(APP, i_pAsset);

	return AOK;
}

static int
F_events(int* i_q, int* i_x, int* i_y) {
	sfEvent t_event;
	
	while (sfRenderWindow_GetEvent(APP, &t_event)) {
		if (t_event.Type == sfEvtKeyPressed) {
			switch (t_event.Key.Code) {
				case sfKeyEscape: *i_q = 1; break;
				case sfKeyNumpad8:
					*i_x -=  0; *i_y -= 16;
					fUI_setMessage(g_pUI, "Hero moves up!");
				break;
				case sfKeyNumpad9: *i_x += 16; *i_y -= 16; break;
				case sfKeyNumpad6: *i_x += 16; *i_y +=  0; break;
				case sfKeyNumpad3: *i_x += 16; *i_y += 16; break;
				case sfKeyNumpad2: *i_x -=  0; *i_y += 16; break;
				case sfKeyNumpad1: *i_x -= 16; *i_y += 16; break;
				case sfKeyNumpad4: *i_x -= 16; *i_y -=  0; break;
				case sfKeyNumpad7: *i_x -= 16; *i_y -= 16; break;
				default: break;
			}
		}
	}

	// Close window : exit
	if (t_event.Type == sfEvtClosed || *i_q) sfRenderWindow_Close(APP);
    
	return AOK;
}

int
main() {
	int t_initReturn;
	if ((t_initReturn = init())) {
		printf("init() failed with code: %d\n", t_initReturn);
		return t_initReturn;
	}

	sfString* t_pText = 0;
	g_pUI = F_UI_create();

	char *t_pMap[] = {
		"###############",
		"#      #      #",
		"#             #",
		"#      ### ####",
		"#### ###   #  #",
		"#          #  #",
		"#          #  #",
		"#             #",
		"#          #  #",
		"###############"
	};

																																																							int t_quit = 0;
	int t_x = 100 + 4 * 16;
	int t_y = 100 + 3 * 16;
	

	// Create a graphical string to display 
	t_pText = sfString_Create();
	sfString_SetFont(t_pText, g_debugFont);
	sfString_SetText(t_pText, "Hello");
	sfString_SetSize(t_pText, 15);
	sfString_SetPosition(t_pText, 100, 100);
	sfColor t_color = {0,0,0,205};
	sfString_SetColor(t_pText, t_color);
	sfClock* t_pClock = sfClock_Create();
	sfClock_Reset(t_pClock);
	float t_last = sfClock_GetTime(t_pClock);	

	fUI_setMessage(g_pUI, "hej");

	int t_frameCount = 0;
	// Start the game loop
	while (sfRenderWindow_IsOpened(APP)) {
		// Process events
		F_events(&t_quit, &t_x, &t_y);
 		
		// Clear the screen
		sfRenderWindow_Clear(APP, sfBlack);
		
		// Update UI
		F_UI_update(g_pUI);

		// Draw the map
		for (int y = 0; y < 15; ++y)
			for (int x = 0; x < 10; ++x) {
				int t_xPos = 100 + x * 16;
				int t_yPos = 100 + y * 16;
				F_draw(MAP, (t_pMap[x][y] == '#')? g_pWall: g_pFloor, t_xPos, t_yPos);	
			}

		// Draw enemy
		F_draw(NPC, g_pNPC, 100 + 3 * 16, 100 + 3 * 16);
		
		// Draw player
		F_draw(PLAYER, g_pPlayer, t_x, t_y); 
		
		// Draw UI
		F_UI_draw(g_pUI, APP);

		// Update the window
		sfRenderWindow_Display(APP);
   	 }
 
	// Cleanup resources
	sfString_Destroy(t_pText);
	sfRenderWindow_Destroy(APP);
 
	return EXIT_SUCCESS;
 }
