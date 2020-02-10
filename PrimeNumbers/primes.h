#include <iostream>
#include <vector>
using namespace std;

class Primes
{
public:
	Primes(uint32_t max); // ��������� ������� ����� � ��������� 1..max
	Primes(); // ��������� ������� ����� ��� ������� �������
	class Iterator;
	Iterator begin();
	Iterator end(); // ��� ���������� ��� ������� ������� end() �������� ������ � ������ ����������
	uint32_t size();
	uint32_t operator[](uint32_t index);
private:
	uint32_t amount;
	vector<uint32_t> data;
};

