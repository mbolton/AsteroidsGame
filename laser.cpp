#define _USE_MATH_DEFINES
#include "laser.h"
#include "ship.h"

using namespace std;
laser::laser(int angle, float shipX, float shipY)
{
	laserX = shipX;
	laserY = shipY;
	laserAngle = angle;
	laserSpeed = 8;

	laserImage = load_bmp("laser.bmp", NULL);
	if (!laserImage)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
}
void laser::refreshLaserLogic()
{
	float radAngle = (((laserAngle) / 256.0) * 360.0) * (M_PI/180.0);
	/* Makes the laser move based on direction, with the constant number representing the speed multiplier. */
	laserX +=  sin(radAngle) * laserSpeed;
	laserY +=  -(cos(radAngle) * laserSpeed);
}
void laser::refreshLaserGraphic(BITMAP *background, BITMAP *buffer)
{
	rotate_sprite(buffer, laserImage, laserX, laserY, itofix(laserAngle));
}
float laser::getLaserX()
{
	return laserX;
}
float laser::getLaserY()
{
	return laserY;
}
laser::~laser(){}
