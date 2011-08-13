#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Graphics/Font.h>

static sfFont* g_debugFont = 0;
static sfWindowSettings WINDOW_SETTINGS = {24, 8, 0}; 
static sfVideoMode VIDEO_MODE = {800, 600, 32};
static sfRenderWindow* APP = 0;
static sfSprite* g_pWall;
static sfSprite* g_pFloor;

typedef enum {
	AOK,
	NO_DEBUG_FONT,
	FAILED_VIDEO_MODE,
	FAILED_LOADING_FONT_FILE
} F_EXIT;

static int
init() {
	// Create the main window
//	int t_modeCount = sfVideoMode_GetModesCount();
//	printf("Graphics mode count: %d\n", t_modeCount);
//	for (int i = 0; i < t_modeCount; ++i) {
//		sfVideoMode t_mode = sfVideoMode_GetMode(i);
//		printf("%dx%d, %dbpp\n", t_mode.Width, t_mode.Height, t_mode.BitsPerPixel);
//	}

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
//	sfImage_Destroy(t_pImage);

	t_pImage = sfImage_CreateFromFile("ass/dirt_floor.png");
        if (!t_pImage) return EXIT_FAILURE;
        g_pFloor = sfSprite_Create();
        sfSprite_SetImage(g_pFloor, t_pImage);
//	sfImage_Destroy(t_pImage);
	
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

int
main() {
	//sfImage* t_pImage;
	sfString* t_pText = 0;
	sfSprite* t_pSprite = 0;
	char *t_pMap[]={
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

	sfEvent t_event;
	int t_quit = 0;
	
     
	int t_initReturn;
        if ((t_initReturn = init())) {
                printf("init() failed with code: %d\n", t_initReturn);
                return t_initReturn;
        }

	// Create a graphical string to display 
	t_pText = sfString_Create();
	sfString_SetFont(t_pText, g_debugFont);
	sfString_SetText(t_pText, "Hello");
	sfString_SetSize(t_pText, 50);
	sfColor t_color = {200,200,200,205};
	sfString_SetColor(t_pText, t_color);
 
	// Start the game loop
	while (sfRenderWindow_IsOpened(APP)) {
		// Process events
		while (sfRenderWindow_GetEvent(APP, &t_event)) {
			if (t_event.Type == sfEvtKeyPressed) {
				if (t_event.Key.Code == sfKeyEscape) {
					t_quit = 1;
				}
			}
 
			// Close window : exit
			if (t_event.Type == sfEvtClosed || t_quit)
                 sfRenderWindow_Close(APP);
         }
 		
		// Clear the screen
		sfRenderWindow_Clear(APP, sfBlack);
		
		// Draw the map
		for (int y = 0; y < 15; ++y)
			for (int x = 0; x < 10; ++x) {
				int t_xPos = 100 + x * 16;
				int t_yPos = 100 + y * 16;
				F_draw(MAP, (t_pMap[x][y] == '#')? g_pWall: g_pFloor, t_xPos, t_yPos);	
			}
		// Draw the string
		sfRenderWindow_DrawString(APP, t_pText);
		// Update the window
		sfRenderWindow_Display(APP);
     }
 
	// Cleanup resources
	sfString_Destroy(t_pText);
	sfRenderWindow_Destroy(APP);
 
	return EXIT_SUCCESS;
 }
