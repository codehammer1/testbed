// primes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>
using namespace std;

int primeBasic(int limit);
int sieveOfAtkin(int limit);

void main()
{
	int limit = 2000000, count1=0, count2=0;
	//count1 = primeBasic(limit);
	count2 = sieveOfAtkin(limit);

	cout << "prime count: " << count2 << "\n";
}

int primeBasic(int limit)
{
	int i,j,prime, count=2;

	for(i=3; i<=limit; i++)
	{
		prime=1;
		for(j=2;j<i;j++)
		{
			if(i%j==0)
			{
				prime=0;
				break;
			}
		}

		if(prime==1)
		{
			count += i;
		}
	}

	return count;
}

int sieveOfAtkin(int limit)
{
	//Create the various different variables required
	int root = (int)ceil(sqrt((double)limit));
	bool *sieve = new bool[limit];
	int *primes = new int[(limit/2)+1];
	int insert = 2;
	primes[0] = 2;
	primes[1] = 3;
	int count = 5;

	for (int z = 0; z < limit; z++) sieve[z] = false;
	for (int x = 1; x <= root; x++)
	{
		for (int y = 1; y <= root; y++)
		{
			// Main part of Sieve of Atkin
			int n = (4*x*x)+(y*y);
			if (n <= limit && (n % 12 == 1 || n % 12 == 5)) sieve[n] ^= true;
			n = (3*x*x)+(y*y);
			if (n <= limit && n % 12 == 7) sieve[n] ^= true;
			n = (3*x*x)-(y*y);
			if (x > y && n <= limit && n % 12 == 11) sieve[n] ^= true;
		}
	}

	// Mark all multiples of squares as non-prime
	for (int r = 5; r <= root; r++) if (sieve[r]) for (int i = r*r; i < limit; i += r*r) sieve[i] = false;

	// Add into prime array
	for (int a = 5; a < limit; a++)
	{
		if (sieve[a])
		{
			primes[insert] = a;
			count += a;
			insert++;
		}
	}

	delete [] sieve;
	delete [] primes;

	return count;
}

