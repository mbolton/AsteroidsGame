#include <allegro.h>
#include <math.h>
#include <iostream>

class ship
{
	public: 
	ship();
	void refreshShip(BITMAP *background, BITMAP *buffer);
	void turnLeft();
	void turnRight();
	void goForward();
	~ship();

	private:
	BITMAP *shipImage;
	int angle;
	float shipX;
	float shipY;
	float speedMult;
};