#include <allegro.h>
#include <math.h>
#include <list>

using namespace std;
class asteroid
{
	public:
	asteroid(BITMAP *img, float x, float y);
	void refreshAsteroidLogic();
	void refreshAsteroidGraphic(BITMAP *background, BITMAP *buffer);
	float getAsteroidX();
	float getAsteroidY();
	~asteroid();

	private:
	BITMAP *asteroidImage;
	int dead;
	float asteroidX;
	float asteroidY;
	float shipX;
	float shipY;
	int asteroidAngle;
	int asteroidSpeed;
};
