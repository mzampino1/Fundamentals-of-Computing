/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 2 Part 2
 * Purpose: To use the principal, interest rate, and desired monthly payment 
 * of a mortgage to display an amortization table followed by a message
 * stating total amount paid and time taken to pay off the mortgage
 */


#include <stdio.h>

int main() {

	// declare/initialize variables
	float interestRate, payment;
	float balance = 0;
	float totalPaid = 0;
	int months = 0;
	
	// welcome user
	printf("Welcome to Mortgage Calculator!\n");
	
	// receive input from user 
	printf("Please enter some information about your mortgage:\n");

	printf("Principal ($): ");
	scanf("%f", &balance);

	// for all 3 inputs:
	// uses while loop to re-prompt user until they enter a valid input
	while(balance < 0) {
		printf("Invalid input, please enter a positive value.\n");
		printf("Principal ($): ");
		scanf("%f", &balance);
	}

	printf("Annual interest rate (%): ");
	scanf("%f", &interestRate);

	
	while(interestRate < 0) {
		printf("Invalid input, please enter a positive value.\n");
		printf("Annual interest rate (%): ");
		scanf("%f", &interestRate);
	}

	printf("Desired monthly payment ($): ");
	scanf("%f", &payment);
	while(payment < 0) {
		printf("Invalid input, please enter a positive value.\n");
		printf("Desired monthly payment ($): ");
		scanf("%f", &payment);
	}

	printf("\n");

	// prevents infinite loop if payment is not high enough
	float interestCharge = ((interestRate/100) * balance / 12);
	if(interestCharge >= payment) {
		printf("Error: your payment is not high enough.\n");
		printf("Payment must be more than: $%.2f\n", interestCharge);
	} else {
		// first line of table
		printf("Month     Payment    Interest      Balance\n");

		// remaining lines in table (with calculations)
		// while loop used so that table ends when balance reaches $0.00
		while(balance) {
			months++;
			printf("%-10d$", months);
			// calculate amount added to balance by interest, adjust balance
			interestCharge = ((interestRate/100) * balance / 12);

			balance += interestCharge;
			
			// adjusts payment to just be the balance if
			// the payment is larger than the balance to prevent negative balance
			// and add accurate amount to totalPaid
			if(balance > payment) {
				totalPaid += payment;
				balance -= payment;
				printf("%6.2f     $", payment);
			} else {
				printf("%6.2f     $", balance);
				totalPaid += (balance);
				balance = 0;
			}

			printf("%6.2f   $", interestCharge);
			printf("%9.2f\n", balance);
		}	

		printf("\n");

		// print total money paid and time taken to pay
		printf("You paid a total of ");
		printf("$%.2f over ", totalPaid);
		
		int years = months / 12;
		months %= 12;

		printf("%d years and %d months.\n", years, months);
	}

	return 0;
}
