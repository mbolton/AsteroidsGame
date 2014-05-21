#include <allegro.h>
#include <math.h>

class laser
{
	public:
	laser(int angle, float shipX, float shipY);
	void refreshLaser(BITMAP *background, BITMAP* buffer);
	int checkAlive();
	~laser();

	private:
	BITMAP *laserImage;
	float laserX;
	float laserY;
	int laserAngle;
	int limit;
	int alive;
};