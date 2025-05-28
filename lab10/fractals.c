/* 
 * Matthew Zampino
 * Fundamentals of Computing - Lab 10
 * Purpose: This program opens an X11 window, then waits for the
 * user to enter a number 1-8, with each number displaying a 
 * different fractal design. The user can press "q" to quit the
 * program.
 */

#include <stdlib.h>
#include <math.h>

#include "gfx.h"

// function prototypes
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void drawSquare(int x, int y, int sideLength);
void shrinkSquares(int x, int y, int sideLength);
void spiralSquares(float radius, float theta, float sideLength);
void circularLace(int xCenter, int yCenter, int radius);
void snowflake(double x, double y, double radius);
void tree(int x, int y, int length, double theta);
void fern(int x, int y, int length, double theta);
void spiralOfSpirals(double xCenter, double yCenter, double radius, double theta);

int main() {

	// used to continue while loop until user presses "q"
	int loop = 1;
	
	int width = 700;
	int height = 700;
	int mrgn = 20;

	gfx_open(width, height, "Fractals");

	while(loop) {
		// waits for user input, clears screen after user presses
		// a button
		char c = gfx_wait();
		gfx_clear();

		// displays appropriate fractal or quits the program based
		// on user input (or clears screen if invalid input
		// is entered)
		switch(c) {
			case '1':
				sierpinski(mrgn, mrgn, width - mrgn, mrgn, width/2, height - mrgn);
				break;
			case '2':
				shrinkSquares(width/2, height/2, 350);
				break;
			case '3':
				spiralSquares(6.0, 0.0, 2.0);
				break;
			case '4':
				circularLace(width/2, height/2, 235);
				break;
			case '5':
				snowflake(width/2, height/2, 235);
				break;
			case '6':
				tree(width/2, height - 20, 220, -M_PI/2);
				break; 
			case '7':
				fern(width/2, height - 20, 450, -M_PI/2);
				break;
			case '8':
				spiralOfSpirals(width/2, height/2, 450, M_PI/2);
				break;
			case 'q':
				loop = 0;
			default:
				break;
		}
	}
}

// draws triangle given 3 points
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

// recursive function to create sierpinski design
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3) {
	// Base case
	if( abs(x2-x1) < 5 ) return;

	// Draw the triangle
	drawTriangle( x1, y1, x2, y2, x3, y3 );

	// Recursive calls
	sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
	sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
	sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

// draws square given coordinates of center and side length
void drawSquare(int x, int y, int sideLength) {
	// top
	gfx_line(x - sideLength/2, y - sideLength/2, x + sideLength/2, y - sideLength/2);
	// right
	gfx_line(x + sideLength/2, y - sideLength/2, x + sideLength/2, y + sideLength/2);
	// bottom
	gfx_line(x + sideLength/2, y + sideLength/2, x - sideLength/2, y + sideLength/2);
	// left
	gfx_line(x - sideLength/2, y + sideLength/2, x - sideLength/2, y - sideLength/2);
}

// recursive function to create shrinking squares design
void shrinkSquares(int x, int y, int sideLength) {
	// base case
	if(sideLength < 2)
		return;

	drawSquare(x, y, sideLength);
	
	// recursive calls at each corner of square, with 7/15 of
	// the side length (top left, top right, bottom right, 
	// bottom left)
	shrinkSquares(x - sideLength/2, y - sideLength/2, 7*sideLength/15);
	shrinkSquares(x + sideLength/2, y - sideLength/2, 7*sideLength/15);
	shrinkSquares(x + sideLength/2, y + sideLength/2, 7*sideLength/15);
	shrinkSquares(x - sideLength/2, y + sideLength/2, 7*sideLength/15);
}

// recursive function to create spiral square design
void spiralSquares(float radius, float theta, float sideLength) {
	// base case
	if(radius > 350)
		return;

	// converts polar coordinates to rectangular (centered at
	// middle of window)
	int x = 350 + radius*cos(theta);
	int y = 350 + radius*sin(theta);

	// draws square at current coordinates
	drawSquare(x, y, sideLength);

	// recursive call, decreasing theta while increasing radius and
	// sideLength
	spiralSquares(radius*1.1, theta - M_PI/6, sideLength*1.1);
}

// recursive function to create circular lace design
void circularLace(int xCenter, int yCenter, int radius) {
	// base case
	if(radius < 2)
		return;
	
	// draws circle
	gfx_circle(xCenter, yCenter, radius);
	
	// recursive calls (6 new circles per circle, each with a radius
	// of 0.33 times the radius of the circle it is attached to)
	for(int i = 0; i < 6; i++) {
		float theta = i * M_PI/3;
		// polar to rectangular coordinates
		int x = xCenter + radius*cos(theta);
		int y = yCenter + radius*sin(theta);
		circularLace(x, y, radius*0.33);
	}
}

// recursive function to make snowflake design
void snowflake(double x, double y, double radius) {
	// base case
	if(radius < 2)
		return;
	
	// draws five lines per snowflake by converting polar to 
	// rectangular coordinates, recursive call at each angle
	for(int i = 0; i < 5; i++) {
		double theta = M_PI/2 + i*2*M_PI/5;
		gfx_line(x, y, x + radius*cos(theta), y + radius*sin(theta));
		snowflake(x + radius*cos(theta), y + radius*sin(theta), radius*0.35);
	}
}

// recursive function to make tree design
void tree(int x, int y, int length, double theta) {
	// base case
	if(length < 2)
		return;
	
	// draws bottom line (trunk)
	int xTopTrunk = x + length*cos(theta);
	int yTopTrunk = y + length*sin(theta);
	gfx_line(x, y, xTopTrunk, yTopTrunk);

	// recursive calls draw branches
	tree(xTopTrunk, yTopTrunk, length*0.67, theta - M_PI/5);
	tree(xTopTrunk, yTopTrunk, length*0.67, theta + M_PI/5);
}

// recursive function to make fern design
void fern(int x, int y, int length, double theta) {
	// base case
	if(length < 4)
		return;
	
	// draws central line (stem) by converting polar to
	// rectangular coordinates
	int xStemOffset = length*cos(theta);
	int yStemOffset = length*sin(theta);
	gfx_line(x, y, x + xStemOffset, y + yStemOffset);
	
	// recursive calls draw 4 branches on central line
	for(int i = 1; i <= 4; i++) {
		fern(x + i*0.25*xStemOffset, y + i*0.25*yStemOffset, 
			 length*0.35, theta - M_PI/5);
		fern(x + i*0.25*xStemOffset, y + i*0.25*yStemOffset, 
			 length*0.35, theta + M_PI/5);
	}
}

// recursive function to make spiral of spirals
void spiralOfSpirals(double xCenter, double yCenter, double radius, double theta) {
	// base case
	if(radius < 1) {
		gfx_point(xCenter, yCenter);
		return;
	}
	
	// makes a smaller spiral at current location in larger spiral
	spiralOfSpirals(xCenter + radius*cos(theta), yCenter + radius*sin(theta),
					radius*0.2, theta);

	// goes to next point in larger spiral
	spiralOfSpirals(xCenter, yCenter, radius*0.95, theta + M_PI/8);
}
