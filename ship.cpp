#include <math.h>
#include "ship.h"
#include <allegro.h>

ship::ship()
{
	
	shipX = SCREEN_W/2;
	shipY = SCREEN_H/2;
	angle = 0;

	shipImage = load_tga("ship3.tga", NULL);
	if (!shipImage)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
	temp = create_bitmap(shipImage -> w, shipImage -> h);
}
void ship::refreshShip(BITMAP *background, BITMAP *buffer)
{
	/* Makes the ship wrap around the map instead of going off of the screen */
	if(shipX < 0)
		shipX = SCREEN_W;
	if(shipX > SCREEN_W)
		shipX = 0;
	if(shipY < 0)
		shipY = SCREEN_H;
	if(shipY > SCREEN_H)
		shipY = 0;

	stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H); // Resets the screen.
	rotate_sprite_trans(buffer, shipImage, shipX, shipY, itofix(angle));
}
void ship::turnLeft()
{
	angle -= 8;
	if(angle < 0)
		angle = 256;
}

void ship::turnRight()
{
	angle += 8;
	if(angle > 256)
		angle = 0;
}

void ship::goForward()
{
   shipY -= 1;
}

ship::~ship(){}
