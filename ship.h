#include <allegro.h>

class ship
{
	public: 
	ship();
	void refreshShip(BITMAP *background, BITMAP *buffer);
	void turnLeft(BITMAP* buffer);
	//void turnRight();
	//void goForward();
	~ship();

	private:
	BITMAP *shipImage;
	BITMAP *temp;
	int angle;
	int shipX;
	int shipY;
	
};