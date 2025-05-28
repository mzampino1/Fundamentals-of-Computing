/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 11
 * Purpose: This program is a recreation of the game "Breakout."
 * This game allows the user to control a paddle at the bottom of the
 * screen using the A and D keys. The goal of the game is to break 
 * all of the bricks at the top of the screen. Bricks must be hit once
 * to break, and some bricks activate power ups when broken. These power
 * ups include a larger paddle, a smaller paddle, another ball spawning, all balls slowing down, 
 * and all balls speeding up. 50 points are gained for each brick broken, 
 * with a 1000 point bonus for each screen cleared. The player has one life,
 * and they lose when all balls go past the paddle and off of the screen.
 */

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "gfx3.h"

// power ups: wider paddle, smaller paddle, slower balls, faster balls, extra ball 
typedef enum {
	NONE,
	WIDE,
	SMALL,
	SLOW,
	FAST,
	BALL
} PowerUp;

// struct for ball
// boolean for whether or not ball is on screen
// x and y components of velocity, x and y position of center, radius
typedef struct {
	bool visible;
	double vx;
	double vy;
	double xc;
	double yc;
	int rad;
} Ball;

// struct for brick
// x and y coordinates of center of brick, number of times brick
// has been hit
typedef struct {
	bool visible;
	int xc;
	int yc;
	int width;
	int height;
	PowerUp power;
} Brick;

// function prototypes
void drawRectangle(int xc, int yc, int width, int height);
void drawBalls(Ball balls[], int maxBalls);
void initializeBalls(Ball balls[], int maxBalls);
void spawnBall(Ball *b, int x, int y);
void welcomeUser(int winWid, int winHeight);
void checkWallCol(Ball balls[], int maxBalls, int winWid, int winHeight);
void moveBalls(Ball balls[], int maxBalls);
void checkPadCol(Ball balls[], int maxBalls, double vPad, int xcPad, int ycPad, int widPad, int htPad);
void newBall(Ball balls[], int maxBalls, int x, int y);
double changeVel(Ball *b, double xcPad, double ycPad, double widPad);
void checkBallCol(Ball balls[], int maxBalls);
int checkOutOfBounds(Ball balls[], int maxBalls, int winHeight);
void initializeBricks(Brick bricks[][6], int brickRows, int brickCols, int winWid, int winHeight);
void drawBricks(Brick bricks[][6], int brickRows, int brickCols);
int checkBrickCol(Ball balls[], int maxBalls, Brick bricks[][6], int brickRows, int brickCols, 
				  int *scorePtr, int *widPadPtr, double *xcPadPtr, int ycPad, int htPad, int winWid);
void displayScore(int score, int winWid);
bool bricksGone(Brick bricks[][6], int brickRows, int brickCols);
bool ballsGone(Ball balls[], int maxBalls);

int main() {

	// used to continue while loop until user presses "q"
	int loop = 1;

	int winWid = 650, winHeight = 650;
	// open window
	gfx_open(winWid, winHeight, "Brick Breaker");

	// width of paddle
	int widPad = 100;
	// height of paddle
	int htPad = 16;
	// coordinates of center of paddle, 20 pixel offset from bottom
	double xcPad = winWid/2, ycPad = 630 - htPad/2;
	// x velocity of paddle
	double vPad = 0;

	int brickRows = 4;
	int brickCols = 6;
	// declare 2D array of bricks
	Brick bricks[brickRows][brickCols];
	initializeBricks(bricks, brickRows, brickCols, winWid, winHeight);

	// maximum of 10 balls at once
	int maxBalls = 10;
	// declare array of balls (max of 5 balls on screen)
	Ball balls[maxBalls];
	// initialize array of balls
	initializeBalls(balls, maxBalls);
	// spawns first ball above paddle
	newBall(balls, maxBalls, xcPad, ycPad - htPad/2 - 11);

	welcomeUser(winWid, winHeight);

	int score = 0;

	while(loop) {
		gfx_clear();

		moveBalls(balls, maxBalls);
		// move paddle (if not at edge)
		if(xcPad + vPad <= winWid - widPad/2 && xcPad + vPad > widPad/2)
			xcPad += vPad;

		checkPadCol(balls, maxBalls, vPad, xcPad, ycPad, widPad, htPad);
		checkBallCol(balls, maxBalls);
		checkBrickCol(balls, maxBalls, bricks, brickRows, brickCols, &score, 
					  &widPad, &xcPad, ycPad, htPad, winWid); 
		checkWallCol(balls, maxBalls, winWid, winHeight);
		int outOfBounds = checkOutOfBounds(balls, maxBalls, winHeight);

		// draw balls and paddle after all movement and collision 
		// checking is done
		drawBalls(balls, maxBalls);
		gfx_color(255, 0, 0);
		drawRectangle(xcPad, ycPad, widPad, htPad);

		// resets bricks and adds 1000 point bonus if all have been destroyed
		if(bricksGone(bricks, brickRows, brickCols)) {
			initializeBricks(bricks, brickRows, brickCols, winWid, winHeight);

			score += 1000;
		}

		drawBricks(bricks, brickRows, brickCols);

		displayScore(score, winWid);

		// displays game over message and option to play again 
		// if all balls go off screen
		if(ballsGone(balls, maxBalls)) {
			gfx_changefont("10x20");
			// red
			gfx_color(255, 0, 0);
			gfx_text(winWid/2 - 45, winHeight/2 + 10, "GAME OVER");

			// white
			gfx_color(255, 255, 255);
			gfx_changefont("8x16");
			gfx_text(winWid/2 - 100, winHeight/2 + 40, "Press space to play again");
		}

		int event = gfx_event_waiting();
		
		if(event != 0) {
			// call gfx_wait() after every event to prevent controls from
			// freezing
			// tolower ensures that capital letters have same effect
			char c = tolower(gfx_wait());
			// runs if key is pressed
			if(event == 1) {
				switch(c) {
					// plays again if balls are gone
					case ' ':
						if(ballsGone(balls, maxBalls)) {
							initializeBalls(balls, maxBalls);
							newBall(balls, maxBalls, xcPad, ycPad - htPad/2 - 11);
							initializeBricks(bricks, brickRows, brickCols, winWid, winHeight);
							score = 0;
							widPad = 100;
						}
						break;
					// exits game
					case 'q':
						loop = 0;
						break;
					// moves paddle left
					case 'a':
						if(vPad == 0 && xcPad - widPad/2 > 0) {
							vPad = -4;
						}
						break;
					// moves paddle right
					case 'd':
						if(vPad == 0 && xcPad + widPad/2 < winWid) {
							vPad = 4;
						}
						break;
					default:
						break;
				}
			}
			// runs if key is released
			if(event == 2) {
				if(c == 'a' || c == 'd') {
					vPad = 0;
				}
			}
			
		}
		gfx_flush();
		usleep(10000);
	}

	return 0;
}

// displays instructions to user before starting game
void welcomeUser(int winWid, int winHeight) {
	gfx_text(winWid/2 - 100, winHeight/2, "Welcome to Brick Breaker!");
	gfx_text(winWid/2 - 100, winHeight/2 + 15, "Hold A or D to move left or right"); 
	gfx_text(winWid/2 - 100, winHeight/2 + 30, "Press Q to quit the game");
	gfx_text(winWid/2 - 100, winHeight/2 + 45, "Press space to start the game");

	// continues only if user presses space
	while(1) {
		char c = gfx_wait();
		if(c == ' ')
			return;
	}
}

// draws rectangle based on center coordinates, width, and height
void drawRectangle(int xc, int yc, int width, int height) {
	int x1 = xc - width/2;
	int y1 = yc - height/2;
	int x2 = xc + width/2;
	int y2 = yc + height/2;
	// top
	gfx_line(x1, y1, x2, y1);
	// right
	gfx_line(x2, y1, x2, y2);
	// bottom
	gfx_line(x2, y2, x1, y2);
	// left
	gfx_line(x1, y2, x1, y1);
}

// moves all balls in array that are on screen
void moveBalls(Ball balls[], int maxBalls) {
	for(int i = 0; i < maxBalls; i++) {
		if(balls[i].visible) {
			balls[i].xc += balls[i].vx;
			balls[i].yc += balls[i].vy;
		}
	}
}

// draws all balls in array that are on screen
void drawBalls(Ball balls[], int maxBalls) {
	// green
	gfx_color(0, 255, 0);
	for(int i = 0; i < maxBalls; i++) {
		// only displays ball and updates position if it is on screen
		if(balls[i].visible)
			gfx_circle(balls[i].xc, balls[i].yc, balls[i].rad);
	}
}

// initializes balls array by ensuring all balls are off screen
void initializeBalls(Ball balls[], int maxBalls) {
	for(int i = 0; i < maxBalls; i++)
		balls[i].visible = false;
}

// spawns ball at given point moving upward and to the right
void spawnBall(Ball *b, int x, int y) {
	b->visible = true;
	b->vx = 2;
	b->vy = -2;
	b->xc = x;
	b->yc = y;
	b->rad = 10;
}

// checks for collisions with right, left, and top walls, adjusts 
// position and velocity accordingly
void checkWallCol(Ball balls[], int maxBalls, int winWid, int winHeight) {
	for(int i = 0; i < maxBalls; i++) {
		// only checks balls on screen
		if(balls[i].visible) {
			// right wall
			if(balls[i].xc + balls[i].rad >= winWid) {
				balls[i].xc = winWid - balls[i].rad - 1;
				balls[i].vx *= -1;
			}
			// left wall
			if(balls[i].xc - balls[i].rad <= 0) {
				balls[i].xc = balls[i].rad + 1;
				balls[i].vx *= -1;
			}
			// top wall
			if(balls[i].yc - balls[i].rad <= 0) {
				balls[i].yc = balls[i].rad + 1;
				balls[i].vy *= -1;
			}
		}
	}
}

// checks if there is any overlap given two ranges of values
bool checkOverlap(int min1, int max1, int min2, int max2) {
	return (max1 >= min2 && max2 >= min1);
}

// function to handle collision of balls with paddle
void checkPadCol(Ball balls[], int maxBalls, double vPad, int xcPad, int ycPad, int widPad, int htPad) {
	for(int i = 0; i < maxBalls; i++) {
		// left edge of ball
		double minXBall = balls[i].xc - balls[i].rad;
		// right edge of ball
		double maxXBall = balls[i].xc + balls[i].rad;
		// left edge of paddle
		double minXPad = xcPad - widPad/2;
		// right edge of paddle
		double maxXPad = xcPad + widPad/2;

		// top edge of ball
		double minYBall = balls[i].yc - balls[i].rad;
		// bottom edge of ball
		double maxYBall = balls[i].yc + balls[i].rad;
		// top edge of paddle
		double minYPad = ycPad - htPad/2;
		// bottom edge of paddle
		double maxYPad = ycPad + htPad/2;

		// change velocity if ball collides with paddle
		if(checkOverlap(minXBall, maxXBall, minXPad, maxXPad)) {
			if(checkOverlap(minYBall, maxYBall, minYPad, maxYPad)) {
				// check for collision direction using previous frame

				// above
				if(maxYBall - balls[i].vy < minYPad) {
					balls[i].yc = ycPad - htPad/2 - balls[i].rad - 1;
				}
				// left
				if(maxXBall - balls[i].vx < minXPad - vPad) {
					balls[i].xc = xcPad - widPad/2 - balls[i].rad - 1;
				}
				// right
				if(minXBall - balls[i].vx > maxXPad - vPad) {
					balls[i].xc = xcPad + widPad/2 + balls[i].rad + 1;
				}
				changeVel(&balls[i], xcPad, ycPad, widPad);
			}
		}
	}
}

// changes velocity of ball based on where the ball hits the paddle
// (angle ranging from 15 to 90 degrees)
double changeVel(Ball *b, double xcPad, double ycPad, double widPad) {
	int dirX = 0;
	if(b->xc < xcPad)
		dirX = -1;
	if(b->xc > xcPad)
		dirX = 1;

	// angle gets smaller when ball hits farther from center of paddle
	double theta = M_PI/2 - (abs(xcPad - b->xc) / (widPad/2 + b->rad))*((5*M_PI)/12);

	// add components of velocity in quadrature to get magnitude
	double velMag = sqrt(b->vy*b->vy + b->vx*b->vx);

	// split velocity back into components based on angle
	b->vx = dirX*cos(theta)*velMag;
	b->vy = -sin(theta)*velMag;
}

// adds a new ball to the screen
void newBall(Ball balls[], int maxBalls, int x, int y) {
	for(int i = 0; i < maxBalls; i++) {
		// return statement ensures only one ball is added to the screen
		if(!balls[i].visible) {
			spawnBall(&balls[i], x, y);
			return;
		}
	}
}

// checks for collisions between balls
// (square hitbox for collision detection)
void checkBallCol(Ball balls[], int maxBalls) {
	int visibleCnt = 0;
	// array of pointers to balls
	Ball *visBalls[maxBalls];
	// make array of visible balls
	for(int i = 0; i < maxBalls; i++) {
		if(balls[i].visible) {
			visBalls[visibleCnt] = &balls[i];
			visibleCnt++;
		}
	}
	// check for collisions between every pair of visible balls
	for(int i = 0; i < visibleCnt; i++) {
		for(int j = i + 1; j < visibleCnt; j++) {
			Ball *b1 = visBalls[i];
			Ball *b2 = visBalls[j];
			// left edge of ball 1
			double minX1 = b1->xc - b1->rad;
			// right edge of ball 1
			double maxX1 = b1->xc + b1->rad;
			// top edge of ball 1
			double minY1 = b1->yc - b1->rad;
			// bottom edge of ball 1
			double maxY1 = b1->yc + b1->rad;
			// left edge of ball 2
			double minX2 = b2->xc - b2->rad;
			// right edge of ball 2
			double maxX2 = b2->xc + b2->rad;
			// top edge of ball 2
			double minY2 = b2->yc - b2->rad;
			// bottom edge of ball 2
			double maxY2 = b2->yc + b2->rad;
			
			if(checkOverlap(minX1, maxX1, minX2, maxX2)) {
				if(checkOverlap(minY1, maxY1, minY2, maxY2)) {
					// check for collision direction using previous frame 
					// and adjust velocities accordingly

					// above
					if(maxY1 - b1->vy < minY2 - b2->vy) {
						b1->yc = b2->yc - b2->rad - b1->rad - 1;
						// swap velocities (elastic collision)
						double temp = b1->vy;
						b1->vy = b2->vy;
						b2->vy = temp;
					}
					// below
					if(minY1 - b1->vy > maxY2 - b2->vy) {
						b1->yc = b2->yc + b2->rad + b1->rad + 1;
						// swap velocities (elastic collision)
						double temp = b1->vy;
						b1->vy = b2->vy;
						b2->vy = temp;
					}
					// left
					if(maxX1 - b1->vx < minX2 - b2->vx) {
						b1->xc = b2->xc - b2->rad - b1->rad - 1;
						// swap velocities (elastic collision)
						double temp = b1->vx;
						b1->vx = b2->vx;
						b2->vx = temp;
					}
					// right
					if(minX1 - b1->vx > maxX2 - b2->vx) {
						b1->xc = b2->xc + b2->rad + b1->rad + 1;
						// swap velocities (elastic collision)
						double temp = b1->vx;
						b1->vx = b2->vx;
						b2->vx = temp;
					}
				}
			}
		}
	}
}

// checks if any balls have gone out of bounds (below bottom of screen)
// sets those balls to invisible and returns number of balls out of bounds
int checkOutOfBounds(Ball balls[], int maxBalls, int winHeight) {
	int cnt = 0;
	for(int i = 0; i < maxBalls; i++) {
		if(balls[i].visible) {
			if(balls[i].yc - balls[i].rad > winHeight) {
				cnt++;
				balls[i].visible = false;
			}
		}
	}
	return cnt;
}

// initializes array of bricks, placing them in appropriate locations 
// and making them visible (maximum of 6 columns)
void initializeBricks(Brick bricks[][6], int brickRows, int brickCols, int winWid, int winHeight) {
	srand(time(NULL));
	for(int i = 0; i < brickRows; i++) {
		for(int j = 0; j < brickCols; j++) {
			bricks[i][j].visible = true;
			// 100 pixel offset from each side with 3 pixel gap
			// between bricks
			bricks[i][j].width = (winWid - 200 - brickCols*3)/brickCols;
			// 50 pixel offset from top of screen with 3 pixel gap
			// between bricks
			bricks[i][j].height = (winHeight/brickRows - 125 - brickRows*3);
			bricks[i][j].xc = 100 + (bricks[i][j].width+3)*j + bricks[i][j].width/2;
			bricks[i][j].yc = 50 + (bricks[i][j].height+3)*i + bricks[i][j].height/2;
			
			bricks[i][j].power = NONE;
			// 1 in 5 chance of assigning random powerup
			if(rand() % 5 == 0) {
				bricks[i][j].power = rand() % 5 + 1; 
			}
		}
	}
}

// draws bricks on screen
void drawBricks(Brick bricks[][6], int brickRows, int brickCols) {
	for(int i = 0; i < brickRows; i++) {
		for(int j = 0; j < brickCols; j++) {
			if(bricks[i][j].visible) {
				// blue
				gfx_color(0, 0, 255);
				drawRectangle(bricks[i][j].xc, bricks[i][j].yc, bricks[i][j].width, bricks[i][j].height);
				if(bricks[i][j].power != NONE) {	
					// white
					gfx_color(255, 255, 255);
					gfx_changefont("10x20");
					switch(bricks[i][j].power) {
						case WIDE:
							gfx_text(bricks[i][j].xc - 20, bricks[i][j].yc + 7, "WIDE");
							break;
						case SMALL:
							gfx_text(bricks[i][j].xc - 25, bricks[i][j].yc + 7, "SMALL");
							break;
						case SLOW:
							gfx_text(bricks[i][j].xc - 20, bricks[i][j].yc + 7, "SLOW");
							break;
						case FAST:
							gfx_text(bricks[i][j].xc - 20, bricks[i][j].yc + 7, "FAST");
							break;
						case BALL:
							gfx_text(bricks[i][j].xc - 20, bricks[i][j].yc + 7, "BALL");
							break;
						default:
							break;
					}
				}
			}
		}
	}
}

// checks for collision between balls and bricks, adjusts velocity of
// ball accordingly, makes brick invisible and adds to score
// returns integer corresponding to powerup in brick
int checkBrickCol(Ball balls[], int maxBalls, Brick bricks[][6], int brickRows, int brickCols, 
				  int *scorePtr, int *widPadPtr, double *xcPadPtr, int ycPad, int htPad, int winWid) {
	for(int i = 0; i < maxBalls; i++) {
		if(balls[i].visible) {
			for(int j = 0; j < brickRows; j++) {
				for(int k = 0; k < brickCols; k++) {
					if(bricks[j][k].visible) {	
						// left edge of ball
						double minXBall = balls[i].xc - balls[i].rad;
						// right edge of ball
						double maxXBall = balls[i].xc + balls[i].rad;
						// left edge of brick
						double minXBrick = bricks[j][k].xc - bricks[j][k].width/2;
						// right edge of brick
						double maxXBrick = bricks[j][k].xc + bricks[j][k].width/2;

						// top edge of ball
						double minYBall = balls[i].yc - balls[i].rad;
						// bottom edge of ball
						double maxYBall = balls[i].yc + balls[i].rad;
						// top edge of brick
						double minYBrick = bricks[j][k].yc - bricks[j][k].height/2;
						// bottom edge of brick
						double maxYBrick = bricks[j][k].yc + bricks[j][k].height/2;

						// reverse velocity if ball collides with paddle
						if(checkOverlap(minXBall, maxXBall, minXBrick, maxXBrick)) {
							if(checkOverlap(minYBall, maxYBall, minYBrick, maxYBrick)) {
								// add 50 points to score
								*scorePtr += 50;
								// make brick invisible
								bricks[j][k].visible = false;
								
								// perform action based on powerup
								switch(bricks[j][k].power) {
									case WIDE:
										if(*widPadPtr <= 300) {
											*widPadPtr += 30;
											if(*xcPadPtr - *widPadPtr < 0)
												*xcPadPtr = *widPadPtr/2 + 1;
											if(*xcPadPtr + *widPadPtr > winWid)
												*xcPadPtr = winWid - *widPadPtr/2 - 1;
										}
										break;
									case SMALL:
										if(*widPadPtr > 40)
											*widPadPtr -= 30;
										break;
									case SLOW:
										// speed must be greater than 1.0 to slow down
										// (5 slow downs max compared to initial speed)
										if(sqrt(abs(balls[i].vy)*abs(balls[i].vy) + abs(balls[i].vx)*abs(balls[i].vx)) > 1.0) {
											// applies to all visible balls
											for(int l = 0; l < maxBalls; l++) {
												if(balls[l].visible) {
													balls[l].vy *= 0.8;
													balls[l].vx *= 0.8;
												}
											}
										}
										break;
									case FAST:
										// speed must be less than 8.6 to speed up 
										// (5 speed ups max compared to initial speed)
										if(sqrt(abs(balls[i].vy)*abs(balls[i].vy) + abs(balls[i].vx)*abs(balls[i].vx)) < 8.6) {
											// applies to all visible balls
											for(int l = 0; l < maxBalls; l++) {
												if(balls[l].visible) {
													balls[l].vy *= 1.25;
													balls[l].vx *= 1.25;
												}
											}
										}
										break;
									case BALL:
										newBall(balls, maxBalls, *xcPadPtr, ycPad - htPad/2 - 11);
										break;
									default:
										break;
								}

								// check for collision direction using previous frame

								// above
								if(maxYBall - balls[i].vy < minYBrick) {
									balls[i].yc = bricks[j][k].yc - bricks[j][k].height/2 - balls[i].rad - 1;
									balls[i].vy *= -1;
								}
								// below
								if(minYBall - balls[i].vy > maxYBrick) {
									balls[i].yc = bricks[j][k].yc + bricks[j][k].height/2 + balls[i].rad + 1;
									balls[i].vy *= -1;
								}
								// left
								if(maxXBall - balls[i].vx < minXBrick) {
									balls[i].xc = bricks[j][k].xc - bricks[j][k].width/2 - balls[i].rad - 1;
									balls[i].vx *= -1;
								}
								// right
								if(minXBall - balls[i].vx > maxXBrick) {
									balls[i].xc = bricks[j][k].xc + bricks[j][k].width/2 + balls[i].rad + 1;
									balls[i].vx *= -1;
								}
							}
						}
					}
				}
			}
		}
	}
}

// displays user's score at top of screen
void displayScore(int score, int winWid) {
	char str[50];
	sprintf(str, "Score: %d", score);

	// magenta
	gfx_color(255, 0, 255);

	gfx_changefont("10x20");
	gfx_text(15, 30, str);
}

// checks if all bricks are invisible, returns true if all
// are invisible and false otherwise
bool bricksGone(Brick bricks[][6], int brickRows, int brickCols) {
	for(int i = 0; i < brickRows; i++) {
		for(int j = 0; j < brickCols; j++) {
			if(bricks[i][j].visible)
				return false;
		}
	}
	return true;
}

// checks if all balls are invisible, returns true if all
// invisible and false otherwise
bool ballsGone(Ball balls[], int maxBalls) {
	for(int i = 0; i < maxBalls; i++) {
		if(balls[i].visible) {
			return false;
		}
	}
	return true;
}
