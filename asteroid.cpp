#define _USE_MATH_DEFINES
#include "asteroid.h"

using namespace std;
asteroid::asteroid(BITMAP *img, float x, float y)
{
	shipX = x;
	shipY = y;
	dead = 0;
	asteroidX = rand() % (SCREEN_W - 80);
	asteroidY = rand() % (SCREEN_H - 80);
	asteroidAngle = rand() % 256;
	asteroidSpeed = rand() % 4 + 1;
	if ((asteroidX > shipX - 200) && (asteroidX < shipX + 200)  && (asteroidY > shipY -200) && (asteroidY < shipY + 200))
	{
		asteroidX += 200;
	}
	asteroidImage = img;
}
void asteroid::refreshAsteroidLogic()
{
	if(asteroidX < 0)
		asteroidX = SCREEN_W;
	if(asteroidX > SCREEN_W)
		asteroidX = 0;
	if(asteroidY < 0)
		asteroidY = SCREEN_H;
	if(asteroidY > SCREEN_H)
		asteroidY = 0; 

	float radAngle = (((asteroidAngle) / 256.0) * 360.0) * (M_PI/180.0);
	/* Makes the laser move based on direction, with the constant number representing the speedmultiplier. */
	asteroidX +=  sin(radAngle) * asteroidSpeed;
	asteroidY +=  -(cos(radAngle) * asteroidSpeed);
}
void asteroid::refreshAsteroidGraphic(BITMAP *background, BITMAP *buffer)
{
	rotate_sprite_trans(buffer, asteroidImage, asteroidX, asteroidY, itofix(asteroidAngle));
}
float asteroid::getAsteroidX()
{
	return asteroidX;
}
float asteroid::getAsteroidY()
{
	return asteroidY;
}

asteroid::~asteroid(){}
