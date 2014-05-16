#include <allegro.h>	
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

	ship = load_bitmap("ship.bmp", NULL);
	if (!ship)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
	set_alpha_blender();
	buffer = create_bitmap(SCREEN_W, SCREEN_H);
	blit(background, buffer, 0,0,0,0, background->w, background->h);

	shipX = SCREEN_W/2;
	shipY = SCREEN_H/2;
	draw_trans_sprite(buffer, ship, shipX, shipY);

	acquire_screen();
	blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
	release_screen();
	
	readkey();    
	return 0;     
}   
END_OF_MAIN();  
