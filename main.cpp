#include <allegro.h>
#include <math.h>
#include <list>
#include <sstream>
#include "ship.h"
#include "laser.h"
#include "asteroid.h"

using namespace std;
int main(void){
	BITMAP *background;
	BITMAP *buffer;

	int score = 0;       // The score based on how many asteroids you have destroyed, each asteroid destroyed is with 1 point.
	int limit = 0;       // Helps limit firing speed.
	int laserSpeed = 20; // Higher means slower firing speed
	int asteroidNum = 0;
	int maxSpawn = 15;
	
	list<laser> laserList;
	list<laser>::iterator iter;

	list<asteroid> asteroidList;
	list<asteroid>::iterator asteroidIter; 

	list<laser>::iterator collisionIter;

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
	
	/* Creates the specified number of asteroids. */

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
		if((asteroidNum < maxSpawn))
		{
				asteroidList.push_back(*new asteroid());
				asteroidNum++;
		}
		iter = laserList.begin();
		asteroidIter = asteroidList.begin();
		
		gameShip.refreshShip(background, buffer);

		/* Refresh loop for the lasers */
		while(iter != laserList.end())
		{
			laser& temp = *iter;
			temp.refreshLaser(background, buffer);
			iter++;
		}

		/* Refresh loop for the asteroids, also doing collision detection */
		while(asteroidIter != asteroidList.end())
		{
			asteroid& tempAsteroid = *asteroidIter;
			tempAsteroid.refreshAsteroid(background,buffer);
			if((gameShip.getShipX() + 39 > tempAsteroid.getAsteroidX()) && (gameShip.getShipX() < tempAsteroid.getAsteroidX() + 39) && (gameShip.getShipY() + 39 > tempAsteroid.getAsteroidY()) && (gameShip.getShipY() < tempAsteroid.getAsteroidY() + 39))
			{
				asteroidIter = asteroidList.erase(asteroidIter);
				asteroidNum--;
				gameShip.gameOver();
			}
			collisionIter = laserList.begin();
			while(collisionIter != laserList.end())
			{
				laser& temp2 = *collisionIter;
				if((temp2.getLaserX() > tempAsteroid.getAsteroidX()) && (temp2.getLaserX() < tempAsteroid.getAsteroidX() + 78) && (temp2.getLaserY() > tempAsteroid.getAsteroidY()) && (temp2.getLaserY() < tempAsteroid.getAsteroidY() + 78))
				{
					tempAsteroid.~asteroid();
					asteroidIter = asteroidList.erase(asteroidIter);
					collisionIter = laserList.erase(collisionIter);
					asteroidNum--;
					score++;
				}
				collisionIter++;
			}
			asteroidIter++;
		}
		textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "Score: %d", score);
		acquire_screen();
		blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
		release_screen();
		rest(10);
	}	 
}   
END_OF_MAIN();  