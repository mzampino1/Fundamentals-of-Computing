/* 
 * Matthew Zampino
 * Fundamentals of Computing - Lab 9 Part 1
 * Purpose: This program opens a window, then waits for the user
 * to press a key or mouse button. When the user presses a certain
 * key or mouse button, it will display the appropriate symbol centered
 * at the current mouse location. A left mouse click displays a blue
 * square outline, "c" displays a white circle, "t" displays a green
 * isosceles triangle, and the numbers 3 through 9 display a purple
 * polygon with a number of sides equal to the number pressed. The 
 * "ESC" key clears the window, and "q" quits the program.
 */

#include <math.h>

#include "gfx.h"

#define SIZE 50

// function prototypes
void drawSquare(int x, int y, int size);
void drawCircle(int x, int y, int size);
void drawTriangle(int x, int y, int size);
void drawPolygon(int x, int y, int numSides, int size);

int main() {

	// open window for symbolic typewriter
	gfx_open(800, 600, "Symbolic Typewriter");

	while(1) {
		// wait for the user to press a button
		char c = gfx_wait();

		// record current mouse location
		int x = gfx_xpos();
		int y = gfx_ypos();

		// perform appropriate action based on button pressed: switch
		// used for square, circle, triangle, and clear; 
		// if statements used for polygons and quit
		switch(c) {
			case 1:
				drawSquare(x, y, SIZE);
				break;
			case 'c':
				drawCircle(x, y, SIZE);
				break;	
			case 't':
				drawTriangle(x, y, SIZE);
				break;
			case 27:
				gfx_clear();
		}
		if(c >= '3' && c <= '9') {
			// number of sides for polygon
			int numSides = c - '0';
			drawPolygon(x, y, numSides, SIZE);
		}
		// exits infinite loop if user presses "q"
		if(c == 'q') 
			break;
	}	
	
	return 0;
}

// draws a blue square with side length size centered at coordinates (x, y)
void drawSquare(int x, int y, int size) {
	// coordinates for top left corner of square
	x -= size/2;
	y -= size/2;
	
	// coordinates for bottom right corner of square
	int x2 = x + size;
	int y2 = y + size;

	// set color to blue
	gfx_color(0, 0, 255);

	// print four lines to make square:

	// top
	gfx_line(x, y, x2, y);
	// right
	gfx_line(x2, y, x2, y2);
	// bottom
	gfx_line(x2, y2, x, y2);
	// left
	gfx_line(x, y2, x, y);
}

// draws a white circle with diameter "size" centered at 
// coordinates (x, y)
void drawCircle(int x, int y, int size) {
	// sets color to white
	gfx_color(255, 255, 255);
	// draws circle
	gfx_circle(x, y, size/2);
}

// draws a green isosceles triangle with a base and height of "size" 
// centered at coordinates (x, y)
void drawTriangle(int x, int y, int size) {
	// sets color to green
	gfx_color(0, 255, 0);

	// draws base (bottom of triangle, left to right)
	gfx_line(x - size/2, y + size/2, x + size/2, y + size/2);
	// draws left side
	gfx_line(x - size/2, y + size/2, x, y - size/2);
	// draws right side
	gfx_line(x + size/2, y + size/2, x, y - size/2);
}

// draws a purple regular polygon with number of sides "numSides", 
// inscribed in a circle of diameter "size" and centered at 
// coordinates (x, y)
void drawPolygon(int x, int y, int numSides, int size) {
	// sets color to purple
	gfx_color(255, 0, 255);

	// radius of circle
	int r = SIZE/2;

	// x1 and y1 represent start of each line, x2 and y2 represent end 
	// of each line
	int x1;
	int y1;
	int x2;
	int y2;

	// use loop to draw polygon based on numSides
	for(int i = 0; i < numSides; i++) {
		// use conversion from polar to rectangular coordinates to draw
		// appropriate line (move 2(pi)/numSides radians from (x1, y1)
		// to (x2, y2))
		x1 = x + r * cos(i*2*M_PI/numSides);
		y1 = y + r * sin(i*2*M_PI/numSides);
		
		x2 = x + r * cos((i+1)*2*M_PI/numSides);
		y2 = y + r * sin((i+1)*2*M_PI/numSides);

		gfx_line(x1, y1, x2, y2);
	}
}
