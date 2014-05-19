#include <allegro.h>	
#include <math.h>
#include "ship.h"
int main(){
	 
	BITMAP *background;
	BITMAP *ship;
	BITMAP *buffer;

	int shipX;
	int shipY;

	allegro_init();
	install_keyboard();

	/*** Creates a window with the set background ***/
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

	ship = load_tga("ship3.tga", NULL);
	if (!ship)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	} 
	buffer = create_bitmap_ex(32, SCREEN_W, SCREEN_H);                       // Creates the buffer for the game to display changes to.

	shipX = SCREEN_W/2;
	shipY = SCREEN_H/2;

	while(!key[KEY_ESC])
	{
		blit(background, buffer, 0,0,0,0, background->w, background->h);
		draw_trans_sprite(buffer, ship, shipX, shipY);

		shipY = shipY - 5;
		shipX = shipX + 5;
		if(shipY < 1)
			shipY = 720;
		if(shipX > 1280)
			shipX = 0;

		acquire_screen();
		blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(10);
	}	 
}   
END_OF_MAIN();  