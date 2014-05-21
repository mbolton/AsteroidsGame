#define _USE_MATH_DEFINES
#include <math.h>
#include "laser.h"
#include "ship.h"
#include <allegro.h>

using namespace std;
laser::laser(int angle, float shipX, float shipY)
{
	laserX = shipX;
	laserY = shipY;
	laserAngle = angle;
	limit = 0;
	alive = 1;

	laserImage = load_bmp("laser.bmp", NULL);
	if (!laserImage)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
}
void laser::refreshLaser(BITMAP *background, BITMAP *buffer)
{
	//if(limit > 30)
		//alive = 0;
	/* Makes the laser wrap around the map instead of going off of the screen */
	/*if(laserX < 0)
		laserX = SCREEN_W;
	if(laserX > SCREEN_W)
		laserX = 0;
	if(laserY < 0)
		laserY = SCREEN_H;
	if(laserY > SCREEN_H)
		laserY = 0; */

	float radAngle = (((laserAngle) / 256.0) * 360.0) * (M_PI/180.0);
	/* Makes the ship move based on direction, with the constant number representing the speedmultiplier. */
	laserX +=  sin(radAngle) * 8;
	laserY +=  -(cos(radAngle) * 8);

	rotate_sprite(buffer, laserImage, laserX, laserY, itofix(laserAngle));
	limit++;
}
int laser::checkAlive()
{
	return alive;
}
laser::~laser(){}