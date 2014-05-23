#define _USE_MATH_DEFINES
#include "ship.h"

using namespace std;
ship::ship()
{
	shipX = SCREEN_W/2;
	shipY = SCREEN_H/2;
	angle = 0;
	speedMult = 3;
	reset = false;

	shipImage = load_tga("ship.tga", NULL);
	if (!shipImage)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
}
void ship::refreshShipLogic()
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
}
void ship::refreshShipGraphic(BITMAP *background, BITMAP *buffer)
{
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
	shipX +=  sin(radAngle) * speedMult;
	shipY +=  -(cos(radAngle) * speedMult);
}

void ship::gameOver()
{
	allegro_message("Game over! Try again!");
	exit(0);
}

float ship::getShipX()
{
	return shipX;
}
float ship::getShipY()
{
	return shipY;
}
int ship::getShipAngle()
{
	return angle;
}
ship::~ship(){}
