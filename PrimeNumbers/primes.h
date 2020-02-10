class Primes
{
public:
	Primes(uint32_t max); // контейнер простых чисел в диапазоне 1..max
	Primes(); // контейнер простых чисел без верхней границы
	class Iterator { … };
	Iterator begin();
	Iterator end(); // для контейнера без верхней границы end() достижим
	только в пустом контейнере
		uint32_t size();
	uint32_t operator[](uint32_t index);
};

