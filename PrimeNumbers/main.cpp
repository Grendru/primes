#include <iostream>
#include <fstream>
#include "primes.h"

using namespace std;


void PrintToFile(char* filename, class Primes myPrimes, char mode)
{
	cout << "Print mode: " << mode << endl;
	ofstream file;
	file.open(filename, ofstream::out);
	if (mode == 'n')
	{
		for (auto it : myPrimes)
		{
			file << it <<  endl;
		}
	}
	else if (mode == 'p')
	{
		for (uint32_t i = 0; myPrimes[i] <= myPrimes.size(); i++)
		{
			file << myPrimes[myPrimes[i]] <<  endl;
		}
	}
	else if (mode == 'g')
	{
		for (auto it : myPrimes)
		{
			if ( IsPrime(2*it + 1) )file << it << endl;
		}
	}
	file.close();
}
int main(int argc, char* argv[])
{
	bool print = false;
	char* FileName = NULL;
	char modePrint = 'n';
	char modeGenerate = 'r';
	uint32_t size = 100;
	for (uint32_t i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-' && (argv[i][1] == 'r' || argv[i][1] == 'q'))
		{
			size = atoi(argv[i + 1]);
			modeGenerate = argv[i][1];
		}
		else if (argv[i][0] == '-' && argv[i][1] == 's' && (argv[i][2] == 'g' || argv[i][2] == 'p'))
		{
			modePrint = argv[i][2];
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'o')
		{
			FileName = argv[i + 1];
			print = true;
		}
	}
	class Primes myPrimes(size, modeGenerate);
	if (print)
	{
		PrintToFile(FileName, myPrimes, modePrint);
	}
	else
	{
		for (auto it : myPrimes)
		{
			cout << it << " ";
		}
	}
}