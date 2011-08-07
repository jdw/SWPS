#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
 
int
main() {
	sfWindowSettings Settings = {24, 8, 0};
	sfVideoMode Mode = {800, 600, 32};
	sfRenderWindow* App;
	sfImage* Image;
	sfSprite* Sprite;
	sfFont* Font;
	sfString* Text;
	sfMusic* Music;
	sfEvent Event;
	int t_quit = 0;
	
	int t_modeCount = sfVideoMode_GetModesCount();
	printf("Graphics mode count: %d\n", t_modeCount);
	for (int i = 0; i < t_modeCount; ++i) {
		sfVideoMode t_mode = sfVideoMode_GetMode(i);
		printf("%dx%d, %dbpp\n", t_mode.Width, t_mode.Height, t_mode.BitsPerPixel);
	}
     
// Create the main window
     App = sfRenderWindow_Create(Mode, "SFML window", sfResize | sfClose, Settings);
     if (!App)
         return EXIT_FAILURE;

     // Load a sprite to display
     Image = sfImage_CreateFromFile("cute_image.jpg");
     if (!Image)
         return EXIT_FAILURE;
     Sprite = sfSprite_Create();
     sfSprite_SetImage(Sprite, Image);
 
     // Create a graphical string to display 
     Font = sfFont_CreateFromFile("FreeMonoBold.ttf", 50, NULL);
     if (!Font)
         return EXIT_FAILURE;
     Text = sfString_Create();
     sfString_SetText(Text, "Hello SFML");
     sfString_SetFont(Text, Font);
     sfString_SetSize(Text, 50);
 
     // Load a music to play
     Music = sfMusic_CreateFromFile("nice_music.ogg");
     if (!Music)
         return EXIT_FAILURE;

     // Play the music
     sfMusic_Play(Music);
 
     // Start the game loop
	while (sfRenderWindow_IsOpened(App)) {
         // Process events
		while (sfRenderWindow_GetEvent(App, &Event)) {
            if (Event.Type == sfEvtKeyPressed) {
				if (Event.Key.Code == sfKeyEscape) {
					t_quit = 1;
				}
			}
 
			// Close window : exit
             if (Event.Type == sfEvtClosed || t_quit)
                 sfRenderWindow_Close(App);
         }
 
         // Clear the screen
         sfRenderWindow_Clear(App, sfBlack);
 
         // Draw the sprite
         sfRenderWindow_DrawSprite(App, Sprite);
 
         // Draw the string
         sfRenderWindow_DrawString(App, Text);
 
         // Update the window
         sfRenderWindow_Display(App);
     }
 
     // Cleanup resources
     sfMusic_Destroy(Music);
     sfString_Destroy(Text);
     sfFont_Destroy(Font);
     sfSprite_Destroy(Sprite);
     sfImage_Destroy(Image);
     sfRenderWindow_Destroy(App);
 
     return EXIT_SUCCESS;
 }
