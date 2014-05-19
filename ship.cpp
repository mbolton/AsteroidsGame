#include <allegro.h>	
#include <math.h>
#include "ship.h"

ship::ship()
{
	
	shipX = SCREEN_W/2;
	shipY = SCREEN_H/2;
	angle = 0;

	shipImage = load_tga("ship3.tga", NULL);
	if (!shipImage)                                                        // Attempts to load the ship image.
	{
		allegro_message("Error! Unable to load ship!");
		exit(0);
	}
	temp = create_bitmap(shipImage-> w, shipImage ->h);
}
void ship::refreshShip(BITMAP *background, BITMAP *buffer)
{
	/* Makes the ship wrap around the map instead of going off of the screen */
	if(shipX < 0)
		shipX = SCREEN_W;
	if(shipX > SCREEN_W)
		shipX = 0;
	if(shipY < 0)
		shipY = SCREEN_H;
	if(shipY > SCREEN_H)
		shipY = 0;

	draw_trans_sprite(buffer, shipImage, shipX, shipY);
	draw_trans_sprite(buffer, temp, 0, 0);
}
void ship::turnLeft(BITMAP *buffer)
{

	clear_to_color(temp, bitmap_mask_color(temp));
	rotate_sprite(temp, shipImage, 0, 0, 64);
	draw_trans_sprite(buffer, temp, shipX, shipY);
}

/*void ship::turnRight()
{
	angle++;
	if(angle > 256)
		angle = 0;
	rotate_sprite(buffer, shipImage, 1280, 720, itofix(angle));
}

void ship::goForward()
{

}*/

ship::~ship(){}
