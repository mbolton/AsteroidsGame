#include <allegro.h>
#include <math.h>

class laser
{
	public:
	laser(BITMAP *img, int angle, float shipX, float shipY);
	void refreshLaserLogic();
	void refreshLaserGraphic(BITMAP *background, BITMAP* buffer);
	float getLaserX();
	float getLaserY();
	~laser();

	private:
	BITMAP *laserImage;
	float laserX;
	float laserY;
	int laserAngle;
	int laserSpeed;
};
