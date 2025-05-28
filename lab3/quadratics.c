/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 3 Part 1
 * Purpose: To calculate the roots of a quadratic equation given three coefficients
 * a, b, and c, reprompting the user until 0 is entered for a
 */

#include <stdio.h>
#include <math.h>

// function prototypes
double calcDisc(double n1, double n2, double n3);
void printResult(double discriminant, double n1, double n2);

int main()
{
	// while loop iterates until break occurs
	while(1) {
		// declare variables for coefficients and discriminant
		double a, b, c, disc;

		// prompt user to enter coefficients or quit immediately when 0 is entered for a
		printf("Enter the coefficients (a,b,c) of a quadratic equation, or enter 0 for a to quit: \n");
		
		scanf("%lf", &a);
		// exits while loop and terminates program if a is zero
		if(!a)
			break;
		scanf("%lf", &b); 
		scanf("%lf", &c);
		
		disc = calcDisc(a, b, c);

		printResult(disc, a, b);
	}
	return 0;
}

// calculates value of the discriminant
double calcDisc(double n1, double n2, double n3) {
	return pow(n2, 2) - 4*n1*n3;
}

// calculates and prints the roots based on discriminant value and a, b values
// using the quadratic formula
void printResult(double discriminant, double n1, double n2) {
	// declare root variables
	double x1, x2;

	if(discriminant > 0) {
		x1 = (-n2 + sqrt(discriminant))/(2*n1);
		x2 = (-n2 - sqrt(discriminant))/(2*n1);
		printf("Roots are: %lf and %lf\n", x1, x2);
	}
	else if(discriminant == 0) {
		x1 = ((-n2/(2*n1)));
		printf("1 root: %lf \n", x1);
	}
	else {
		printf("No real solutions.\n");
	}
}

