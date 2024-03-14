
#include "../include/BitArray.h"
using namespace std;

BitArray& BitArray::reset(int n) {
	if (n > len || n < 0)
		throw WrongNum(n, __func__);
	arr[n / 32] &= ~(1 << n);
	return *this;
}
//Заполняет массив ложью.
BitArray& BitArray::reset() {
	for (int i = 0; i < len; i++)
		this->reset(i);
	return *this;
}

BitArray::BitArray() {
	if (!arr) {
		arr = new long[1];
		arr[0] = 0;
		len = 32;
	}
	else {
		cout << "Array was already created" << endl;
	}
}


void BitArray::resize(int num_bits, bool value) {
	BitArray tmp = BitArray(num_bits, 0);
	if (arr != NULL)
		memcpy(tmp.arr, arr, (num_bits / 32 < len / 32) ? (num_bits / 32) + 1 : (len / 32) + 1);
	else
		len = 0;
	if (num_bits > len) {
		for (int i = len; i < num_bits; i++) {
			tmp.set(i, value);
		}
	}
	arr = tmp.arr;
	len = num_bits;
}
BitArray::BitArray(int num_bits, unsigned long value) {
	arr = new long[num_bits / 32 + 1];
	len = num_bits;
	arr[0] = value;
}
BitArray::BitArray(const BitArray& b) {
	if (b.empty())
		throw WrongArr(__func__);
	BitArray r(b.len, 0);
	for (int i = 0; i < r.len; i++)
	{
		r.set(i, b[i]);
	}
	delete[] arr;
	arr = r.arr;
	len = r.len;
}


BitArray::~BitArray() {
}

BitArray& BitArray::set(int n, bool val) {
	if (n > len)
		throw WrongNum(n, __func__);
	if (val)
		arr[n / 32] |= 1 << n;
	else
		arr[n / 32] &= ~(1 << n);
	return *this;
}

BitArray& BitArray::set() {
	for (int i = 0; i < len; i++) {
		this->set(i, true);
	}
	return *this;
}

void BitArray::push_back(bool bit)
{
	len++;
	if (len / 32 > (len - 1) / 32) {
		long* tmp = new long[len - 1 / 32 + 1];
		memcpy(tmp, arr, 1 + ((len - 1) / 32));
		delete[] arr;
		arr = tmp;
	}

	this->set(len - 1, bit);
}


void BitArray::clear() {
	delete[] arr;
	arr = NULL;
	len = 0;
}

void BitArray::printArr() {
	for (int i = 0; i < len; i++) {
		if (i % 32 == 0)
			cout << " ";
		if ((*this)[i])
			cout << 1;
		else
			cout << 0;

	}
	cout << endl;
}

void BitArray::swap(BitArray& b) {
	BitArray tmp;
	tmp.arr = this->arr;
	tmp.len = this->len;
	this->arr = b.arr;
	this->len = b.len;
	b.arr = tmp.arr;
	b.len = tmp.len;
}
