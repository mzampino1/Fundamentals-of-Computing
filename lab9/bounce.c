/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 9 Part 2
 * Purpose: This program displays an animation of a ball moving around
 * the window at a constant velocity, bouncing off of the walls of the
 * window. When the user clicks on the screen, the ball will be launched 
 * from that point with a random velocity. The user can press "q" to
 * quit the program.
 */

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "gfx.h"

// function prototypes
void randomizeVelocity(int *dx, int *dy);
void handleCollision(int *x, int *y, int *dx, int *dy, int rad, int wid, int height);

int main() {

	int wid = 800, height = 600; // dimensions of window
	int x = 400, y = 300; // coordinates of center of circle
	int rad = 20; // radius of circle
	
	// randomizes seed for future calls to rand()
	srand(time(NULL));

	int dx, dy;
	randomizeVelocity(&dx, &dy);

	// open window
	gfx_open(wid, height, "Bouncing Ball");

	while(1) {
		// clears screen, draws circle, flushes output to window
		gfx_clear();
		gfx_circle(x, y, rad);
		gfx_flush();

		x += dx;
		y += dy;

		handleCollision(&x, &y, &dx, &dy, rad, wid, height);
		
		// performs following section if user has pressed a button
		if(gfx_event_waiting()) {
			char c = gfx_wait();
			// ends animation when user presses "q"
			if(c == 'q')
				break;
			// places ball at mouse location and randomizes velocity 
			// if user clicks
			if(c == 1) {
				x = gfx_xpos();
				y = gfx_ypos();
				randomizeVelocity(&dx, &dy);
			}	
		}
		usleep(10000);
	}

	return 0;
}

// assigns random values (from 1 to 5) to dx and dy 
// (x and y components of velocity, values can be positive
// or negative)
void randomizeVelocity(int *dx, int *dy) {
	// gives sign random value
	int sign;
	if(rand() % 2 == 0)
		sign = 1;
	else
		sign = -1;

	// gives velocity components random values (positive or negative)
	*dx = sign * (rand() % 5 + 1); 
	*dy = sign * (rand() % 5 + 1);
}

// flips sign of appropriate component of velocity and adjusts
// position if ball collides with wall
void handleCollision(int *x, int *y, int *dx, int *dy, int rad, int wid, int height) {
	// right wall
	if(*x + rad >= wid) {
		*dx *= -1;
		// rightmost coordinate of ball should be at x = wid - 1
		*x = wid - rad - 1; 
	}
	// left wall
	if(*x - rad < 0) {
		*dx *= -1;
		// leftmost coordinate of ball should be at x = 0
		*x = rad; 
	}
	// bottom wall
	if(*y + rad >= height) {
		*dy *= -1;
		*y = height - rad - 1;
	}
	// top wall
	if(*y - rad < 0) {
		*dy *= -1;
		*y = rad;
	}
}
