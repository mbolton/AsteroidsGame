#include <allegro.h>
#include <math.h>
#include <list>
#include "ship.h"
#include "laser.h"

using namespace std;
int main(void){
	BITMAP *background;
	BITMAP *buffer;

	list<laser> laserList;
	list<laser>::iterator iter;
	int limit = 0;       // Helps limit firing speed.
	int laserSpeed = 20; // Higher means slower firing speed.
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

	background = load_tga("background.tga", NULL);
	if (!background)                                                  // Attempts to load the background image.
	{
		allegro_message("Error! Unable to load background!");
		exit(0);
	}
	ship gameShip;

	buffer = create_bitmap_ex(32, SCREEN_W, SCREEN_H);                // Creates the buffer for the game to display changes to.
	blit(background, buffer, 0,0,0,0, background->w, background->h);
	
	while(!key[KEY_ESC])
	{
		stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);	
		if(keypressed())
		{
			if(key[KEY_W])
				gameShip.goForward(); 
			if(key[KEY_A])
				gameShip.turnLeft();
			if(key[KEY_D])
				gameShip.turnRight();
			if(key[KEY_SPACE])
			{
				if(limit == laserSpeed) // Makes the limit iterate through being called a number of times before firing, to limit the firing speed.
				{
					laserList.push_back(*new laser(gameShip.getShipAngle(), gameShip.getShipX(), gameShip.getShipY()));
					limit = 0;
				}
				limit++;
			}
		} 		
		iter = laserList.begin();
		
		gameShip.refreshShip(background, buffer);
		while(iter != laserList.end())
		{
			laser& temp = *iter;
			temp.refreshLaser(background, buffer);
			iter++;
		}
		
		acquire_screen();
		blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(10);
	}	 
}   
END_OF_MAIN();  