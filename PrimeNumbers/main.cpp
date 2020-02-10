#include <iostream>
#include <fstream>
#include "primes.h"

using namespace std;

void PrintToFile(char* filename, class Primes* myPrimes)
{
	ofstream file;
	file.open(filename, ofstream::out);
	for (auto it : *myPrimes)
	{
		file << it << " " << endl;
	}
	file.close();
}
int main(int argc, char* argv[])
{
	//cout << argc << endl << argv[1] << endl;
	class Primes* myPrimes = NULL;
	if (argc == 1) //запуск приложения по умолчанию
	{
		class Primes temp(100,'r');
		for (auto it : temp)
		{
			cout << it << " " << endl;
		}
	}
	else
	{
		bool print = false;
		for (uint32_t i = 0; i < argc; i++)
		{
			if (argv[i][0] == '-' && (argv[i][1] == 'r' || argv[i][1] == 'q'))
			{
				class Primes temp(atoi(argv[i+1]), argv[i][1]);
				myPrimes = &temp;
				print = true;
			}
			else if (argv[i][0] == '-' && argv[i][1] == 'o')
			{
				if (print) PrintToFile(argv[i + 1], myPrimes);
				print = false;
			}
		}
		if (print)
		{
			for (auto it : *myPrimes)
			{
				cout << it << " ";
			}
		}
	}
}