/*
 * Matthew Zampino
 * Fundamentals of Computing - Lab 4 Part 2
 * Purpose: This program uses the sieve of Eratosthenes algorithm to find and
 * print all prime numbers between 1 and 1,000, displaying them in rows
 * with up to 10 numbers per row.
 */

#include <stdio.h>

// function parameters
void initializeArray(int primes[]);
void completeSieve(int primes[]);
void printPrimes(int primes[]);

int main() {

	// declare array
	int primes[1000];

	// these two functions can change the array primes 
	// because arrays are passed by reference
	initializeArray(primes);
	completeSieve(primes);

	printPrimes(primes);

	return 0;
}

// use for loop to initialize all array elements to 1
void initializeArray(int primes[]) {
	for(int i = 0; i < 1000; i++) {
		primes[i] = 1;
	}
}


// implement sieve of Eratosthenes algorithm
// elements at indices corresponding to non-prime numbers are set to 0
// comments indicate efficiency enhancements
void completeSieve(int primes[]) {
	// handle even indices before main loop (which handles odd indices)
	for(int i = 4; i <= 1000; i += 2)
		primes[i] = 0;

	// stop at i = 31, which is the last integer before the square root of 1000 (31.6),
	for(int i = 3; i <= 31; i+= 2) {
		// if statement checks that number is prime before completing inner loop
		if(primes[i]) {
			// start j at i*i, and increment j by i to only set multiples of i to 0
			for(int j = i*i; j <= 1000; j += i) {
				primes[j] = 0;
			}
		}
	}
}


// print prime numbers in rows with maximum 10 integers, starting at index 2
// use rowCount variable to ensure each row is 10 integers wide
void printPrimes(int primes[]) {
	int rowCount = 0;
	for(int i = 2; i < 1000; i++) {
		if(primes[i] == 1) {
			printf("%4d", i);
			// adds to rowCount, prints new line and resets rowCount 
			// to 0 if rowCount is 10 (10 integers in row)
			rowCount++;
			if(rowCount == 10) {
				printf("\n");
				rowCount = 0;
			}
		}
	}
	printf("\n");
}
