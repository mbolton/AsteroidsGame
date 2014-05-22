#include <allegro.h>
#include <math.h>
#include <list>

using namespace std;
class ship
{
	public: 
	ship();
	void refreshShip(BITMAP *background, BITMAP *buffer);
	void turnLeft();
	void turnRight();
	void goForward();
	void gameOver();
	/** Allows main to get the necessary information about the ship. */
	float getShipX();
	float getShipY();
	int getShipAngle();
	~ship();

	private:
	BITMAP *shipImage;
	int angle;
	float shipX;
	float shipY;
	float speedMult;
};