//Includes
#include <stdio.h>
#include <string>
#include "functions.cpp"
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>


//prototypes of function
void Hanoi(unsigned int n, char source,char dest,char help);

int main (int argc, char *argv[])
{
	long n = 0; //The amount of blocks.
	/* If the amount of blocks was passed through a command line argument use it: */
	if (argc > 1)
	{
		n = strtol(argv[1],NULL,10); //Extract the # of blocks from CLI arguments and assign it to n.
		/* If n has an incorrect value, ask the user to input a correct one: */
		if (n <= 0)
		{
			cerr << "Please enter a valid integer" << endl;
			n = getinteger(10);
		}
	}
	/* If no number of blocks was passed via command line, ask the user to input a number: */
	else
	{
		n = getinteger(10);
	}
	Hanoi(n, 'a','b','c');
	return 0;
}

void Hanoi(unsigned int n, char source,char dest,char help)
{
	if (n==1)
	{
		printf("Move disk from %c to %c\n",source,dest);
	}

	else //if n>1
	{
		Hanoi(n-1,source,help,dest);
		printf("Move disk from %c to %c\n", source, dest);
		Hanoi(n-1,help,dest,source);
	}
}
