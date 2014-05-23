#include <allegro.h>
#include <math.h>
#include <list>
#include <sstream>
#include "ship.h"
#include "laser.h"
#include "asteroid.h"

using namespace std;

volatile int speedCounter = 0;
static void speedCounterUpdater()
{
	speedCounter++;
}
END_OF_STATIC_FUNCTION(speedCounterUpdater);
int main(void){
	BITMAP *background;
	BITMAP *buffer;
	BITMAP *shipImage;
	BITMAP *laserImage;
	BITMAP *asteroidImage;

	int score = 0;       // The score based on how many asteroids you have destroyed, each asteroid destroyed is with 1 point.
	int limit = 0;       // Helps limit firing speed.
	int laserSpeed = 20; // Higher means slower firing speed
	int asteroidNum = 0;
	int maxSpawn = 50;
	
	
	list<laser> laserList;
	list<laser>::iterator iter;
	list<laser>::iterator iter2;

	list<asteroid> asteroidList;
	list<asteroid>::iterator asteroidIter;
	list<asteroid>::iterator asteroidIter2;  

	list<laser>::iterator collisionIter;

	/*** Initialized the program and creates a window with the set background ***/
	allegro_init();
	install_timer();
	install_keyboard();
	set_color_depth(32);
	set_alpha_blender();

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1400, 1050, 0, 0) != 0)  // Attempts to set the graphic mode.
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
	shipImage = load_tga("ship.tga", NULL);
	if (!shipImage)                                                  // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship image!");
		exit(0);
	}
	laserImage = load_bmp("laser.bmp", NULL);
	if (!laserImage)                                                  // Attempts to load the laser image.
	{
		allegro_message("Error! Unable to load laser image!");
		exit(0);
	}
	asteroidImage = load_tga("asteroid.tga", NULL);
	if (!asteroidImage)                                                  // Attempts to load the asteroid image.
	{
		allegro_message("Error! Unable to load asteroid image!");
		exit(0);
	}

	ship gameShip(shipImage);

	buffer = create_bitmap_ex(32, SCREEN_W, SCREEN_H);                // Creates the buffer for the game to display changes to.
	blit(background, buffer, 0,0,0,0, background->w, background->h);
	
	LOCK_FUNCTION(speedCounterUpdate);
	LOCK_VARIABLE(speedCounter);
	install_int_ex(speedCounterUpdater, BPS_TO_TIMER(60));

	while(!key[KEY_ESC])
	{	
		while(speedCounter > 0)
		{
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
						laserList.push_back(*new laser(laserImage, gameShip.getShipAngle(), gameShip.getShipX(), gameShip.getShipY()));
						limit = 0;
					}
					limit++;
				}
			} 	
			if((asteroidNum < maxSpawn))
			{
				asteroidList.push_back(*new asteroid(asteroidImage, gameShip.getShipX(), gameShip.getShipY()));
					asteroidNum++;
			} 
			iter = laserList.begin();
			asteroidIter = asteroidList.begin();

			gameShip.refreshShipLogic();
			/* Refresh loop for the lasers */
			while(iter != laserList.end())
			{
				laser& temp = *iter;
				temp.refreshLaserLogic();
				iter++;
			}
			/* Refresh loop for the asteroids, also doing collision detection */
			while(asteroidIter != asteroidList.end())
			{
				asteroid& tempAsteroid = *asteroidIter;
				tempAsteroid.refreshAsteroidLogic();
				if((gameShip.getShipX() + 42 > tempAsteroid.getAsteroidX()) && (gameShip.getShipX() < tempAsteroid.getAsteroidX() + 78) && (gameShip.getShipY() + 42 > tempAsteroid.getAsteroidY()) && (gameShip.getShipY() < tempAsteroid.getAsteroidY() + 78))
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
			speedCounter--;
		}

		iter2 = laserList.begin();
		asteroidIter2 = asteroidList.begin();
		
		stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);	
		gameShip.refreshShipGraphic(background, buffer);
		/* Graphic Refresh loop for the lasers */
		while(iter2 != laserList.end())
		{
			laser& temp2 = *iter2;
			temp2.refreshLaserGraphic(background, buffer);
			iter2++;
		}
		/* Graphic refresh loop for the asteroids. */
		while(asteroidIter2 != asteroidList.end())
		{
			asteroid& tempAsteroid2 = *asteroidIter2;
			tempAsteroid2.refreshAsteroidGraphic(background,buffer);
			asteroidIter2++;
		}
		textprintf_ex(buffer, font, 10, 10, makecol(255, 255, 255), -1, "Score: %d", score);
		acquire_screen();
		blit(buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
		release_screen();
	}
}   
END_OF_MAIN();  
