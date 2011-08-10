#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include <SFML/Graphics/Font.h>

sfFont* g_debugFont = 0;
static sfWindowSettings WINDOW_SETTINGS = {24, 8, 0}; 
static sfVideoMode VIDEO_MODE = {800, 600, 32};
static sfRenderWindow* APP;

typedef enum {
	AOK,
	NO_DEBUG_FONT,
	FAILED_VIDEO_MODE,
	FAILED_LOADING_FONT_FILE
} F_EXIT;

static int
init() {
	// Loading debug font
	g_debugFont = sfFont_CreateFromFile("ass/FreeSerif.ttf", 50, NULL);
	if (!g_debugFont) return FAILED_LOADING_FONT_FILE;

	return AOK;
}

int
main() {
	sfImage* t_pImage;
	sfString* t_pText = 0;
	sfSprite* t_pSprite = 0;

	int t_initReturn;
	if ((t_initReturn = init())) {
		printf("init() failed with code: %d\n", t_initReturn);
		return t_initReturn;
	}

	sfEvent t_event;
	int t_quit = 0;
	
	int t_modeCount = sfVideoMode_GetModesCount();
	printf("Graphics mode count: %d\n", t_modeCount);
	for (int i = 0; i < t_modeCount; ++i) {
		sfVideoMode t_mode = sfVideoMode_GetMode(i);
		printf("%dx%d, %dbpp\n", t_mode.Width, t_mode.Height, t_mode.BitsPerPixel);
	}
     
	// Create the main window
	APP = sfRenderWindow_Create(VIDEO_MODE, "SWPS", sfResize | sfClose, WINDOW_SETTINGS);
	if (!APP) return EXIT_FAILURE;

	// Load a sprite to display
	t_pImage = sfImage_CreateFromFile("ass/cute_image.jpg");
	if (!t_pImage) return EXIT_FAILURE;
	t_pSprite = sfSprite_Create();
	sfSprite_SetImage(t_pSprite, t_pImage);

	// Create a graphical string to display 
	t_pText = sfString_Create();
	sfString_SetFont(t_pText, g_debugFont);
	sfString_SetText(t_pText, "Hello");
	sfString_SetSize(t_pText, 50);
	sfColor t_color = {200,200,200,5};
 
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
 		// Draw the sprite
		sfRenderWindow_DrawSprite(APP, t_pSprite);
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
