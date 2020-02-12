/*!
\file
\brief Исходный файл с реализацией методов классов и функций.

Данный файл содержит в себе реализацию функции IsPrime(), а также методов классов Primes и Primes::Iterator.
*/
#include "primes.h"
/*!
Проверяет полученное число на простоту методом пробного деления. Такой метод используется, основываясь на предположении, что класс будет применяться для работы с относительно небольшими числами.
\param[in] n Проверяемое число
\return true, если число простое, false иначе
*/
bool IsPrime(uint32_t n)
{
	if (n == 1 || n == 2) return true;
	if (n % 2 == 0) return false;
	for (uint32_t i = 3; i <= sqrt(n); i += 2)
	{
		if (n % i == 0) return false;
	}
	return true;
}

/*!
Создает контейнер на основе входных параметров
\param[in] max В зависимости от режима либо максимальное значение, до которого рассчитываются и запоминаются
простые числа, либо количество простых чисел, начиная с 1, которые требуется рассчитать и запомнить.
\param[in] mode Режим генерации элементов контейнера ('r' - поиск простых чисел в диапозоне от 1 до max, 'q' - поиск первых max простых чисел)
*/
Primes::Primes(uint32_t max, char mode)
{
	amount = 0;
	data = NULL;
	if (mode == 'r')
	{
		system("tput civis -- invisible");
		uint32_t period = max/1000 == 0 ? 1 : max/1000;
		for (uint32_t i = 1; i < max; i++)
		{
			if (IsPrime(i))
			{
				amount++;
				uint32_t* temp = new uint32_t[amount];
				memcpy(temp, data, sizeof(uint32_t) * (amount - 1));
				temp[amount - 1] = i;
				if (data != NULL)
					delete[] data;
				data = temp;
			}
			if (i % period == 0)
			{
				float per = (float) i/max;
				cout << "\b\b\b\b\b\b\b"<< std::setprecision(1)<< std::fixed << per*100 << "%  " ;
			}
		}
		cout << "\b\b\b\b\b\b\b\b\b\b\b100%          " << endl; 
		system("tput cnorm   -- normal");

	}
	else if (mode == 'q')
	{
		uint32_t i = 0;
		system("tput civis -- invisible");
		uint32_t period = max/1000 == 0 ? 1 : max/1000;
		while (amount != max)
		{
			if (IsPrime(i))
			{
				amount++;
				uint32_t* temp = new uint32_t[amount];
				memcpy(temp, data, sizeof(uint32_t) * (amount - 1));
				temp[amount - 1] = i;
				if (data != NULL)
					delete[] data;
				data = temp;
			}
			if (amount % period == 0)
			{
				float per = (float) amount/max;
				cout << "\b\b\b\b\b\b\b"<< std::setprecision(1)<< std::fixed << per*100 << "%  " ;
			}
			i++;
		}
		cout << "\b\b\b\b\b\b\b\b\b\b\b100%          " << endl; 
		system("tput cnorm   -- normal");
	}
}
/*!
\return Итератор на первый элемент.
\throw Cпецификация noexcept
*/
Primes::Iterator Primes::begin() noexcept
{
	return Iterator(data);
}
/*!
\return Итератор на элемент, следующий за последним элементом контейнера.
\throw Cпецификация noexcept
*/
Primes::Iterator Primes::end() noexcept
{
	return Iterator(data + amount);
}
/*!
\return Количетсво элементов в контейнере.
*/
uint32_t Primes::size()
{
	return amount;
}

/*!
Возвращает ссылку на элемент по индексу index.  
\warning Проверка на выход за границы не выполняется.
\return Ссылку на элемент контейнера с индексом index
*/
reference Primes::operator[](uint32_t index)
{
	return data[index];
}



/*!
Создает контейнер на основе другого контейнера путем копирования.
\param[in] other Копируемый контейнер.
*/
Primes::Primes(const Primes& other) : amount(other.amount)
{
	data = new uint32_t[amount];
	memcpy(data, other.data, sizeof(uint32_t) * amount);
}
/*!
Создает контейнер на основе другого контейнера путем перемещения.
\param[in] other Контейнер, данные которого перемещаеются в создаваемый.
*/
Primes::Primes(Primes&& other) : data(other.data)
{
	other.amount = 0;
	other.data = nullptr;
}


/*!
Создает итератор элемента контейнера.
\param[in] p Указатель на элемент контейнера.
*/
Primes::Iterator::Iterator(pointer p) : cur(p) {}
/*!
\return Результат операции сложения, применимой к итератору.
*/
reference Primes::Iterator::operator+(uint32_t n)
 {
	return *(cur + n); 
 }
/*!
\return Результат операции вычитания, применимой к итератору.
*/
reference Primes::Iterator::operator-(uint32_t n) 
{ 
	return *(cur - n); 
}
/*!
\return Результат операции префиксной инкрементации, применимой к итератору.
*/
reference Primes::Iterator::operator++(int) 
{ 
	return *cur++; 
}

/*!
\return Результат операции префиксной декрементации, применимой к итератору.
*/
reference Primes::Iterator::operator--(int) 
{ 
	return *cur--; 
}
/*!
\return Результат операции постфиксной инкрементации, применимой к итератору.
*/
reference Primes::Iterator::operator++() 
{ 
	return *++cur; 
}
/*!
\return Результат операции постфиксной декрементации, применимой к итератору.
*/
reference Primes::Iterator::operator--() 
{ 
	return *--cur; 
}

/*!
\return Результат операции != , применимой к двум итераторам.
*/
bool Primes::Iterator::operator!=(const Iterator& it) 
{ 
	return cur != it.cur; 
}
/*!
\return Результат операции ==, применимой к двум итераторам.
*/
bool Primes::Iterator::operator==(const Iterator& it) 
{ 
	return cur == it.cur; 
}

/*!
\return Результат операции <, применимой к двум итераторам.
*/
bool Primes::Iterator::operator<(const Iterator& it) 
{ 
	return cur < it.cur; 
}
/*!
\return Результат операции >, применимой к двум итераторам.
*/
bool Primes::Iterator::operator>(const Iterator& it) 
{ 
	return cur > it.cur; 
}
/*!
\return Результат операции <=, применимой к двум итераторам.
*/
bool Primes::Iterator::operator<=(const Iterator& it) 
{ 
	return cur <= it.cur; 
}
/*!
\return Результат операции >=, применимой к двум итераторам.
*/
bool Primes::Iterator::operator>=(const Iterator& it) 
{ 
	return cur >= it.cur; 
}
/*!
\return Ссылку на элемент по указателю, содержащемуся в итераторе.
*/
reference Primes::Iterator::operator*() 
{ 
	return *cur; 
}