#include <iostream>

using namespace std;

#include "compl.h"

int main() {
	cout << "Testy : if there are no errors, then test is passed" << endl;
	ones_compl_int<signed char> first(-63);
	ones_compl_int<signed char> one(1);
	ones_compl_int<signed char> up(63);
	for (; first <= up; first += one) {
		for (int j = -63; j <= 63; j++) {
			ones_compl_int<signed char> second(j);
			ones_compl_int<signed char> result = first + second;
			if ((int)(signed char)(first.value() + j) != (int)(signed char)result.value())
				 std::cout << "ERROR (" << (int)first.value() << ")+(" << (int)j << ") != " << (int)(signed char)(first.value() + j) << " : " << (int)(signed char)result.value() << " obtained!" << std::endl;
		}
	}
	for (int i = 0; i < 127; i++) {
		ones_compl_int<signed char> first(i);
		for (int j = 0; j < 127; j++) {
			ones_compl_int<signed char> second(j);
			ones_compl_int<signed char> result = first - second;
			if ((int)(signed char)(i - j) != (int)(signed char)result.value())
				std::cout << "ERROR (" << (int)i << ")-(" << (int)j << ") != " << (int)(signed char)(i - j) << " : " << (int)(signed char)result.value() << " obtained!" << std::endl;
		}
	}
	for (int i = -255; i < 255; i++) {
		ones_compl_int<signed int> first(i);
		for (int j = -255; j < 255; j++) {
			ones_compl_int<signed int> second(j);
			ones_compl_int<signed int> result = first * second;
			if ((int)(signed int)(i * j) != (int)(signed int)result.value())
				std::cout << "ERROR (" << (int)i << ")*(" << (int)j << ") != " << (int)(signed int)(i * j) << " : " << (int)(signed int)result.value() << " obtained!" << std::endl;
		}
	}
	for (int i = -1000; i < 1000; i++) {
		ones_compl_int<signed int> first(i);
		for (int j = -1000; j < 1000; j++) {
			ones_compl_int<signed int> second(j);
			ones_compl_int<signed int> result = first / second;
			if (j == 0) continue;
			if ((int)(signed int)(i / j) != (int)(signed int)result.value())
				std::cout << "ERROR (" << (int)i << ")/(" << (int)j << ") != " << (int)(signed int)(i / j) << " : " << (int)(signed int)result.value() << " obtained!" << std::endl;
		}
	}

	return 0;
}
