# primes

Приложение принимает на вход аргументы командной строки. Поддерживаются следующие команды:

	-r [n]		- поиск простых в диапозоне от 2 до n;
	-q [n]          - поиск первых n простых чисел;
	-o [fileName]   - вывод содержимого контейнера в указанный файл;
	-sg		- вывод только простых чисел Софи Жермен;
	-sp		- вывод только суперпростых чисел;
	-st [fileName]  - вывод статистики в указанный файл. 
 
Команды вводятся через пробел. Первые две команды и команды -sg, -sp соответсвенно взаимоисключающие. Пример запуска программы:

./primes -q 100 -o output.txt -sp -st stat.txt		

- создание контейнера, содержащего первые 100 простых чисел, вывод только суперпростых чисел в файл output.txt, запись статистики в файл stat.txt.

Documentations link: https://grendru.github.io/primes/PrimeNumbers/documentations/index.html
