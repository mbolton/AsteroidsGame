#include <allegro.h>
#include <math.h>
#include <list>

using namespace std;
class asteroid
{
	public:
	asteroid();
	void refreshAsteroid(BITMAP *background, BITMAP *buffer);
	~asteroid();

	private:
	BITMAP *asteroidImage;
	int dead;
	float asteroidX;
	float asteroidY;
	int asteroidAngle;
	int asteroidSpeed;
};