/*!
\file
\brief Заголовочный файл с описанием классов и функций.

Данный файл содержит в себе определение функции IsPrime(), а также классов Primes и Primes::Iterator.
*/
#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>

using namespace std;
typedef uint32_t* pointer; ///< Указатель на элемент типа uint32_t
typedef uint32_t& reference; ///< Ссылка на элемент типа uint32_t


bool IsPrime(uint32_t n);///< Функция проверки числа на простоту.


/*!
	\brief Класс-контейнер простых чисел

	Данный класс содержит в себе контейнер простых чисел и методы работы с ним.
*/
class Primes
{
public:
	Primes(uint32_t max, char mode); ///< Создаёт объект класса Primes.
	Primes(const Primes& other); ///< конструктор копирования.
	Primes(Primes&& other); ///< конструктор перемещения.
	class Iterator;
	Iterator begin() noexcept; ///< Возвращает итератор на первый элемент контейнера. 
	Iterator end() noexcept; ///< Возвращает итератор на элемент, следующий за последним элементом контейнера.
	uint32_t size(); ///< Возращает количество элементов в контейнере.
	reference operator[](uint32_t index); ///<  Предоставляет доступ к указанному элементу.
private:
	uint32_t* data;
	uint32_t amount;
};

/*!
	\brief Итератор контейнера простых чисел

	Данный класс содержит в себе методы итератора
*/
class Primes::Iterator
{
private:
	pointer cur;
public:
	Iterator(pointer p);
	reference operator+(uint32_t n);
	reference operator-(uint32_t n);

	reference operator++(int);
	reference operator--(int);
	reference operator++();
	reference operator--();

	bool operator!=(const Iterator& it);
	bool operator==(const Iterator& it);
	bool operator<(const Iterator& it);
	bool operator>(const Iterator& it);
	bool operator<=(const Iterator& it);
	bool operator>=(const Iterator& it);
	reference operator*();

	friend class Primes;
};