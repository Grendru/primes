#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>


using namespace std;
typedef uint32_t* pointer;
typedef uint32_t& reference;


bool IsPrime(uint32_t n);


class Primes
{

public:
	Primes(uint32_t max, char mode); // контейнер простых чисел в диапазоне 1..max
	Primes(const Primes& other);
	Primes(Primes&& other);
	class Iterator
	{
	private:
		pointer cur;
	public:
		Iterator(pointer p) : cur(p) {}
		reference operator+(uint32_t n) { return *(cur + n); }
		reference operator-(uint32_t n) { return *(cur - n); }


		reference operator++(int) { return *cur++; }
		reference operator--(int) { return *cur--; }
		reference operator++() { return *++cur; }
		reference operator--() { return *--cur; }


		bool operator!=(const Iterator& it) { return cur != it.cur; }
		bool operator==(const Iterator& it) { return cur == it.cur; }
		bool operator<(const Iterator& it) { return cur < it.cur; }
		bool operator>(const Iterator& it) { return cur > it.cur; }
		bool operator<=(const Iterator& it) { return cur <= it.cur; }
		bool operator>=(const Iterator& it) { return cur >= it.cur; }
		reference operator*() { return *cur; }

		friend class Primes;
	};
	Iterator begin() noexcept;
	Iterator end() noexcept; // для контейнера без верхней границы end() достижим только в пустом контейнере
	uint32_t size();
	reference operator[](uint32_t index);
private:
	uint32_t* data;
	uint32_t amount;
};

