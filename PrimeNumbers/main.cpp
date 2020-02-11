﻿#include <iostream>
#include <fstream>
#include <iomanip>
#include <intrin.h>
#include "primes.h"

using namespace std;
#pragma intrinsic(__rdtsc)

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
		auto SophieLambda = [](uint32_t p) { return IsPrime(2 * p + 1); };
		for (auto it : myPrimes)
		{
			if (SophieLambda(it) )file << it << endl;
		}
	}
	file.close();
}
int main(int argc, char* argv[])
{
	bool print = false, statisticMode = false;
	char *fileName = NULL, *statisticFile = NULL;
	char modePrint = 'n';
	char modeGenerate = 'r';
	unsigned __int64 timeStart, time;
	uint32_t size = 100;
	for (uint32_t i = 1; i < argc; i++)
	{
		if ((argv[i][0] == '-' && (argv[i][1] == 'r' || argv[i][1] == 'q')) && argv[i][2] == '\0' && (argv[i+1][0] >= '0' && argv[i + 1][0] <= '9'))
		{
			size = atoi(argv[i + 1]);
			modeGenerate = argv[i][1];
			i++;
		}
		else if (argv[i][0] == '-' && argv[i][1] == 's' && (argv[i][2] == 'g' || argv[i][2] == 'p') && argv[i][3] == '\0')
		{
			modePrint = argv[i][2];
		}
		else if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == 't' && argv[i][3] == '\0' && (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z' || argv[i + 1][0] >= 'A' && argv[i + 1][0] <= 'Z' || argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9'))
		{
			statisticMode = true;
			statisticFile = argv[i + 1];
			i++;
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'o' && argv[i][2] == '\0' && (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z' || argv[i + 1][0] >= 'A' && argv[i + 1][0] <= 'Z' || argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9'))
		{
			fileName = argv[i + 1];
			print = true;
			i++;
		}
		else
		{
			cout << "[error]: Unknown command \"" << argv[i] << "\"" << endl;
			exit(1);
		}
	}
	if (statisticMode)
	{
		timeStart = __rdtsc();
	}
	class Primes myPrimes(size, modeGenerate);
	if (statisticMode)
	{
		time = __rdtsc() - timeStart;
		ofstream file;
		file.open(statisticFile, ofstream::app);
		file << "[" << setw(6) << myPrimes.size() << "]: " << setw(10) << time
			<< " tacts"<< setw(15) << uint64_t(myPrimes.size()) + uint64_t((myPrimes.size() - 1)) * sizeof(uint32_t) << " bytes" << endl;
		file.close();
	}
	if (print)
	{
		PrintToFile(fileName, myPrimes, modePrint);
	}
	else
	{
		if (modePrint == 'n')
		{
			for (auto it : myPrimes)
			{
				cout << it << " ";
			}
		}
		else if (modePrint == 'p')
		{
			for (uint32_t i = 0; myPrimes[i] <= myPrimes.size(); i++)
			{
				cout << myPrimes[myPrimes[i]] << " ";
			}
		}
		else if (modePrint == 'g')
		{
			for (auto it : myPrimes)
			{
				if (IsPrime(2 * it + 1)) cout << it << " ";
			}
		}
	}
}