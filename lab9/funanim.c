/* 
 * Matthew Zampino
 * Fundamentals of Computing - Lab 9 Part 3
 * Purpose: This programs displays an animation of a white clock with
 * minute, hour, and second hands of different colors that move at 
 * appropriate rates relative to one another. The user can control the
 * speed of the clock using the up and down arrow keys, and there are
 * 5 possible speeds. The user can press "q" to quit.
 */

#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "gfx.h"

// function prototypes
void welcomeUser();
void displayTicks(int xCenter, int yCenter, int rad);
void displaySecond(int xCenter, int yCenter, int rad, double tSecond);
void displayMinute(int xCenter, int yCenter, int rad, double tMinute);
void displayHour(int xCenter, int yCenter, int rad, double tHour);
void displayTable(int xCenter, int yCenter, int wid, int height, int rad);

int main() {

	welcomeUser();

	int wid = 600, height = 600; // dimensions of window
	int rad = 250; // radius of clock
	int speed = 1; // speed setting (1-5)

	// relative speed of each hand: 1 second per tick, 
	// 1 minute per 60 ticks, 1 hour per 720 ticks.
	// (1 hour per 720 ticks because it moves at 1/12th the rate of
	// the minute hand)
	double dSec = 1.0, dMinute = 1.0/60, dHour = 1.0/720; 

	// angle of each hand
	double tSec = -M_PI/2, tMinute = -M_PI/2, tHour = -M_PI/2;

	gfx_open(wid, height, "Clock");

	int xCenter = 300, yCenter = 300; // coordinates of center of clock

	while(1) {
		// if there is user input, completes appropriate action
		if(gfx_event_waiting()) {
			char c = gfx_wait();
			// if the user presses a number 1-5, adjusts speed
			switch(c) {
				case '1':
					speed = 1;
					break;
				case '2':
					speed = 2;
					break;
				case '3':
					speed = 3;
					break;
				case '4':
					speed = 4;
					break;
				case '5':
					speed = 5;
					break;
			}
			if(c == 'q')
				break;
		}

		gfx_color(255, 255, 255);
		gfx_circle(xCenter, yCenter, rad);

		displayTable(xCenter, yCenter, wid, height, rad);
		displayTicks(xCenter, yCenter, rad);

		// displays hands
		displaySecond(xCenter, yCenter, rad, tSec);
		displayMinute(xCenter, yCenter, rad, tMinute);
		displayHour(xCenter, yCenter, rad, tHour);
		
		// changes angle of hands (rotates them), greater change at
		// higher speeds
		tSec += speed*dSec*(2*M_PI/60);
		tMinute += speed*dMinute*(2*M_PI/60);
		tHour += speed*dHour*(2*M_PI/60);

		gfx_flush();

		gfx_clear();
		usleep(10000);	
	}
	
	return 0;
}

// welcomes user, gives instructions for how to control the clock
// then waits for user to press enter before continuing program
void welcomeUser() {
	printf("Welcome to Clock Animation!\n");
	printf("Use the numbers 1-5 to control the clock's speed.\n");
	printf("The default speed is 1 (slowest).\n");
	printf("Press \"q\" to quit.\n\n");
	printf("Please press enter to open the animation.\n");

	// waits until user presses enter to continue
	while(getchar() != '\n');
}

// displays ticks on the clock (12 large ticks, 60 small ticks)
void displayTicks(int xCenter, int yCenter, int rad) {
	// large ticks 
	for(int i = 1; i <= 12; i++) {
		double cosAngle = cos((i*2*M_PI)/12); // cosine of current angle
		double sinAngle = sin((i*2*M_PI)/12); // sine of current angle
		
		// start of line is on edge of circle 
		// (multiply by 0.996 (249/250) to prevent overlapping pixels)
		int x1 = xCenter + 0.996*rad*cosAngle;
		int y1 = yCenter + 0.996*rad*sinAngle;

		// end of line is 1/10th of the way into the circle
		int x2 = xCenter + 0.9*rad*cosAngle;
		int y2 = yCenter + 0.9*rad*sinAngle;

		// set color to red
		gfx_color(255, 0, 0);
		gfx_line(x1, y1, x2, y2);
	}
	// small ticks
	for(int i = 1; i <= 60; i++) {
		// prevents overlapping with large ticks
		if(i % 5 != 0) {
			double cosAngle = cos((i*2*M_PI)/60); // cosine of current angle
			double sinAngle = sin((i*2*M_PI)/60); // sine of current angle
			
			// start of line is on edge of circle 
			// (multiply by 0.996 (249/250) to prevent overlapping pixels)
			int x1 = xCenter + 0.996*rad*cosAngle;
			int y1 = yCenter + 0.996*rad*sinAngle;

			// end of line is 1/20th of the way into the circle
			int x2 = xCenter + 0.95*rad*cosAngle;
			int y2 = yCenter + 0.95*rad*sinAngle;

			// set color to yellow
			gfx_color(255, 255, 0);
			gfx_line(x1, y1, x2, y2);
		}
	}
}

// displays second hand
void displaySecond(int xCenter, int yCenter, int rad, double tSecond) {
	// set color to blue
	gfx_color(0, 0, 255);
	gfx_line(xCenter, yCenter, xCenter + 0.85*rad*cos(tSecond), yCenter + 0.85*rad*sin(tSecond));
}

// displays minute hand
void displayMinute(int xCenter, int yCenter, int rad, double tMinute) {
	// set color to green
	gfx_color(0, 255, 0);
	gfx_line(xCenter, yCenter, xCenter + 0.7*rad*cos(tMinute), yCenter + 0.7*rad*sin(tMinute));
}

// displays hour hand
void displayHour(int xCenter, int yCenter, int rad, double tHour) {
	// set color to magenta
	gfx_color(255, 0, 255);
	gfx_line(xCenter, yCenter, xCenter + 0.5*rad*cos(tHour), yCenter + 0.5*rad*sin(tHour));
}

// displays brown rectangle on bottom of screen (representing a table)
void displayTable(int xCenter, int yCenter, int wid, int height, int rad) {
	// set color to brown
	gfx_color(102, 51, 0);

	// displays solid table
	for(int i = height - 1; i > height - 50; i--) {
		gfx_line(xCenter - rad, i, xCenter + rad, i);
	}
}
