#include <allegro.h>
	
int main(){
	 
	BITMAP *background;
	
	allegro_init();
	install_keyboard();

	/*** Creates a window with the set background ***/
	set_color_depth(desktop_color_depth());
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
	blit(background, screen, 0,0,0,0, background->w, background->h);
	
	readkey();    
	return 0;
	     
}   
END_OF_MAIN();  
