#include <allegro.h>
#include <math.h>
#include "ship.h"
int main(void){
	 
	BITMAP *background;
	BITMAP *buffer;

	/*** Initialized the program and creates a window with the set background ***/
	allegro_init();
	install_keyboard();
	set_color_depth(32);
	set_alpha_blender();

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0) != 0)  // Attempts to set the graphic mode.
	{
		allegro_message("Error! Can not set graphic mode!"); 
		exit(0);
	}	

	background = load_bitmap("background.bmp", NULL);
	if (!background)                                                  // Attempts to load the background image.
	{
		allegro_message("Error! Unable to load background!");
		exit(0);
	}
	buffer = create_bitmap_ex(32, SCREEN_W, SCREEN_H);                // Creates the buffer for the game to display changes to.

	ship gameShip;

	blit(background, buffer, 0,0,0,0, background->w, background->h);
	
	while(!key[KEY_ESC])
	{
		if(keypressed())
		{
			if(key[KEY_W])
				gameShip.goForward(); 
			if(key[KEY_A])
				gameShip.turnLeft();
			if(key[KEY_D])
				gameShip.turnRight(); 
		} 
		
		gameShip.refreshShip(background, buffer);
		acquire_screen();
		blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(10);
	}	 
}   
END_OF_MAIN();  