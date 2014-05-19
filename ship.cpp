#include <allegro.h>	
#include <math.h>
#include "ship.h"

ship::ship()
{
	BITMAP *shipImage;
	BITMAP *temp;
	int angle = 0;

	shipImage = load_tga("ship3.tga", NULL);
	if (!shipImage)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
}

/*void ship::turnLeft()
{
	angle++;
	if(angle < 0)
		angle = 256;
	rotate_sprite(buffer, ship, 1280, 720, itofix(angle));
}

void ship::turnRight()
{
	angle++;
	if(angle > 256)
		angle = 0;
	rotate_sprite(buffer, ship, 1280, 720, itofix(angle));
}

/*void ship::goForward()
{

}*/

ship::~ship(){}
