#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>

static sfFont* t_debugFont = 0;
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
	t_debugFont = sfFont_CreateFromFile("ass/FreeMonoBold.ttf", 50, NULL);
    if (!t_debugFont) return FAILED_LOADING_FONT_FILE;
    //Text = sfString_Create();
	//sfString_SetText(Text, "Hello SFML");
	//sfString_SetFont(Text, Font);
	//sfString_SetSize(Text, 50);

	return AOK;
}

int
main() {
	//sfRenderWindow* App;
	//sfImage* Image;
	//sfString* Text;
	
	int t_initReturn;
	if ((t_initReturn = init())) {
		printf("init() failed with code: %d\n", t_initReturn);
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
	//Image = sfImage_CreateFromFile("cute_image.jpg");
	//if (!Image) return EXIT_FAILURE;
	//Sprite = sfSprite_Create();
	//sfSprite_SetImage(Sprite, Image);

	// Create a graphical string to display 
	//Text = sfString_Create();
    //sfString_SetText(Text, "Hello SFML");
    //sfString_SetFont(Text, Font);
    //sfString_SetSize(Text, 50);
 
     // Load a music to play
     //Music = sfMusic_CreateFromFile("nice_music.ogg");
     //if (!Music) return EXIT_FAILURE;

	// Play the music
    //sfMusic_Play(Music);
 
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
         //sfRenderWindow_Clear(App, sfBlack);
 
         // Draw the sprite
         //sfRenderWindow_DrawSprite(App, Sprite);
 
         // Draw the string
         //sfRenderWindow_DrawString(App, Text);
 
         // Update the window
         sfRenderWindow_Display(APP);
     }
 
	// Cleanup resources
	//sfMusic_Destroy(Music);
	//sfString_Destroy(Text);
	sfFont_Destroy(t_debugFont);
	//sfSprite_Destroy(Sprite);
	//sfImage_Destroy(Image);
	sfRenderWindow_Destroy(APP);
 
	return EXIT_SUCCESS;
 }
