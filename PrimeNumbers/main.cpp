#include <iostream>
#include "primes.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << argc << endl << argv[1] << endl;
	if (argc == 1) //запуск приложения по умолчанию
	{
		class Primes myPrimes(100,'r');
		//class Primes::Iterator it(myPrimes.begin());
		for (auto it : myPrimes)
		{
			cout << it << " " << endl;
		}
	}
	else
	{
		if (argv[1][0] == '-')
		{
			class Primes myPrimes(atoi(argv[2]), argv[1][1]);
			for (auto it : myPrimes)
			{
				cout << it << " " << endl;
			}
		}
	}
}