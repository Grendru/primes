/*!
\file
\brief Основной файл программы

Данный файл содержит в себе функции main(), PrintStatistic() и PrintToFile().
*/
#include <fstream>
#include <signal.h>
#include "primes.h"

#ifdef _WIN32
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

/*!
Выводит сообщение о прерывании выполнения программы по прерыванию пользователя.
*/
void keyInterrupt(int sig)
{
	cout << endl << "Program interrupted by user" << endl;
	system("tput cnorm   -- normal");
	exit(1);
}
/*!
Осуществляет запись статистики в указанный файл.
\param[in] fileName Имя файла для записи.
\param[in] time Время создания контейнера в тактах процессора.
\param[in] volumeMemory Объем памяти, затраченной во время создания контейнера.
\param[in] size Количество элементов контейнера.
\warning Оценка объема памяти выполянется приблизительно
*/
void PrintStatistic(char* fileName, uint64_t time, uint32_t volumeMemory, uint32_t size)
{
	ofstream file;
	file.open(fileName, ofstream::app);
	file << "[" << setw(6) << size<< "]: " << setw(10) << time
		<< " tacts" << setw(15) << volumeMemory << " bytes" << endl;
	file.close();
}
/*!
Осуществляет запись содержащихся в контейнере объектов в файл
\param[in] filename Имя файла для записи
\param[in] myPrimes Контейнер
\param[in] mode Режим печати ('n' - печать всех элементов, 'g' - печать только простых чисел Софи Жермен, 'r' - печать только суперпростых чисел)
*/
void PrintToFile(char* filename, class Primes myPrimes, char mode)
{
	ofstream file;
	file.open(filename, ofstream::out);
	if (mode == 'n')
	{
		for (auto it : myPrimes)
		{
			file << it << endl;
		}
	}
	else if (mode == 'p')
	{
		for (uint32_t i = 0; myPrimes[i] <= myPrimes.size(); i++)
		{
			file << myPrimes[myPrimes[i]] << endl;
		}
	}
	else if (mode == 'g')
	{
		auto SophieLambda = [](uint32_t p) { return IsPrime(2 * p + 1); };
		for (auto it : myPrimes)
		{
			if (SophieLambda(it))file << it << endl;
		}
	}
	file.close();
}
/*!
Выполняет парсинг аргументов командной строки, вызов всех требуемых функций и методов, при надобности производит вывод информации в консоль.
\param Аргументы командной строки.
*/
int main(int argc, char* argv[])
{
	bool print = false, statisticMode = false;
	char* fileName = NULL, * statisticFile = NULL;
	char modePrint = 'n';
	char modeGenerate = 'r';
	uint64_t timeStart, time, volumeMemory;
	uint32_t size = 100;
	signal(SIGINT, keyInterrupt); 
	//signal(SIGTSTP, keyInterrupt); 
	for (uint32_t i = 1; i < argc; i++)
	{
		if ((argv[i][0] == '-' && (argv[i][1] == 'r' || argv[i][1] == 'q')) && argv[i][2] == '\0' && (argv[i + 1][0] >= '0' && argv[i + 1][0] <= '9'))
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
	cout << "Start creating a container" << endl;
	class Primes myPrimes(size, modeGenerate);
	cout << "Creation comlete" << endl;
	if (statisticMode)
	{
		time = __rdtsc() - timeStart;
		volumeMemory = uint64_t(myPrimes.size()) + uint64_t((myPrimes.size() - 1)) * sizeof(uint32_t) ;
		PrintStatistic(statisticFile,time,volumeMemory, myPrimes.size());
		cout << "Statistics recorded" << endl;
	}
	if (print)
	{
		cout << "Writing to file " << fileName << " started" << endl;
		PrintToFile(fileName, myPrimes, modePrint);
		cout << "Writing comleted" << endl;

	}
	else
	{
		if (modePrint == 'n')
		{
			for (auto it : myPrimes)
			{
				cout << it << " ";
			}
			cout << endl;
		}
		else if (modePrint == 'p')
		{
			for (uint32_t i = 0; myPrimes[i] <= myPrimes.size(); i++)
			{
				cout << myPrimes[myPrimes[i]] << " ";
			}
			cout << endl;
		}
		else if (modePrint == 'g')
		{
			for (auto it : myPrimes)
			{
				if (IsPrime(2 * it + 1)) cout << it << " ";
			}
			cout << endl;
		}
	}
}