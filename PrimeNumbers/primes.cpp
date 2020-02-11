#include "primes.h"

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
Primes::Primes(uint32_t max, char mode)
{
	amount = 0;
	data = NULL;
	if (mode == 'r')
	{
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
		}
	}
	else if (mode == 'q')
	{
		uint32_t i = 0;
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
			i++;
		}
	}
}
Primes::Iterator Primes::begin() noexcept
{
	return Iterator(data);
}
Primes::Iterator Primes::end() noexcept
{
	return Iterator(data + amount);
}
uint32_t Primes::size()
{
	return amount;
}
reference Primes::operator[](uint32_t index)
{
	return data[index];
}




Primes::Primes(const Primes& other) : amount(other.amount)
{
	data = new uint32_t[amount];
	memcpy(data, other.data, sizeof(uint32_t) * amount);
}
Primes::Primes(Primes&& other) : data(other.data)
{
	other.amount = 0;
	other.data = nullptr;
}