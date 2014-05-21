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
	float getShipX();
	float getShipY();
	int getShipAngle();
	void fireBullet(BITMAP *background, BITMAP *buffer);
	~ship();

	private:
	BITMAP *shipImage;
	int angle;
	float shipX;
	float shipY;
	float speedMult;
	
};