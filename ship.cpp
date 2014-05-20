#define _USE_MATH_DEFINES
#include <math.h>
#include "ship.h"
#include <allegro.h>
#include <iostream>
using namespace std;
ship::ship()
{
	shipX = SCREEN_W/2;
	shipY = SCREEN_H/2;
	angle = 0;
	speedMult = 2.5;

	shipImage = load_tga("ship3.tga", NULL);
	if (!shipImage)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
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
	angle -= 4;
	if(angle < 0)
		angle = 256;
}

void ship::turnRight()
{
	angle += 4;
	if(angle > 256)
		angle = 0;
}

void ship::goForward()
{
   /* Convert the angle to radians */
	float radAngle = (((angle) / 256.0) * 360.0) * (M_PI/180.0);
	/* Makes the ship move based on direction, with the constant number representing the speedmultiplier. */
	shipX +=  sin(radAngle) * 3;
	shipY +=  -(cos(radAngle) * 3);

}
ship::~ship(){}
