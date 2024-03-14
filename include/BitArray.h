#ifndef PROJECT1_H_
#define PROJECT1_H_

#include <iostream> // IO access
#include <algorithm>
#include <cstring>
#include <iterator>
#include <stdio.h>
#include <string>
#include <exception>

using namespace std;


class WrongLen {
public:
	long len1, len2;
	const char* s;
	WrongLen(long l, long l2, const char* s) : len1(l), len2(l2), s(s) {};
	virtual void what() const noexcept
	{
		cout << "Invalid size of arrays in function: " << s << endl;
		cout  << "A array size: " << len1 << endl;
		cout  << "B array size: " << len2 << endl;
	}
};

class WrongNum {
public:
	int num;
	const char* s;
	WrongNum(int num, const char* s) : num(num), s(s) {};
	virtual void what() const noexcept
	{
		cout << "Invalid number in function: " << s << endl;
		cout << "Number: " << num << endl;
	}
};

class WrongArr {
public:
	const char* s;
	WrongArr(const char* s) : s(s) {};
	virtual void what() const noexcept
	{
		cout << "Invalid varible in function: " << s << "\n" << "Array is empty" << endl;
	}
};

using namespace std;
class BitArray {
public:
	// init bitarray with 32 bits
	BitArray();
	~BitArray();
	// delete array
	//explicit BitArray(int num_bits, unsigned long value = 0);
	BitArray& set(int n, bool val = true);
	explicit BitArray(int num_bits, unsigned long value = 0);
	BitArray& operator=(const BitArray& b) {
		if (b.empty())
			throw WrongArr(__func__);
		BitArray tmp = BitArray(b.len, 0);
		for (int i = 0; i < len; i++)
		{
			tmp.set(i, b[i]);
		}
		arr = tmp.arr;
		len = tmp.len;
		return *this;
	}
	bool any() const {
		if ((*this).empty())
			throw WrongArr(__func__);
		for (int i = 0; i < len; i++) {
			if ((*this)[i] != 0)
				return 1;
		}
		return 0;
	}
	BitArray operator~() const {
		if ((*this).empty())
			throw WrongArr(__func__);
		for (int i = 0; i < len / 32 + 1; i++) {
			arr[i] = ~arr[i];
		}
		return *this;
	}
	//true, если все биты массива ложны.
	bool none() const {
		return (!this->any());
	}
	BitArray(const BitArray& b);
	void printArr();
	void swap(BitArray& b);
	bool operator[](int i) const {
		if ((*this).empty())
			throw WrongArr(__func__);
		if (i < len)
			return ((1) & (arr[i / 32] >> i));
		else
			throw WrongNum(len, __func__);
	}
	BitArray& reset(int n);
	//Заполняет массив ложью.
	BitArray& reset();
	void resize(int num_bits, bool value = false);
	//Очищает массив.
	void clear();
	//Добавляет новый бит в конец массива. В случае необходимости 
	//происходит перераспределение памяти.
	void push_back(bool bit);
	BitArray& set();
	int size() const {
		return len;
	}
	bool empty() const {
		if (arr == NULL || len == 0)
			return 1;
		return 0;
	}
	string to_string() const {
		string res;
		for (int i = 0; i < len; i++) {
			if ((*this)[i]) {
				res += '1';
			}
			else
				res += '0';
		}
		return res;
	}

	BitArray& operator&=(const BitArray& b) {
		if (b.len != len) {
			throw WrongLen(len, b.len, __func__);
		}
		BitArray r(b.size(), 0);
		for (int i = 0; i < r.size(); i++) {
			r.set(i, b[i] & (*this)[i]);
		}
		delete[] arr;
		arr = r.arr;
		return *this;
	}
	BitArray& operator|=(const BitArray& b) {
		if (b.len != len) {
			throw WrongLen(b.len, len, __func__);
		}
		BitArray r(b.size(), 0);
		for (int i = 0; i < r.size(); i++) {
			r.set(i, b[i] | (*this)[i]);
		}
		delete[] arr;
		arr = r.arr;
		len = r.len;
		
		return *this;
	}
	BitArray& operator^=(const BitArray& b) {
		if (b.len != len) {
			throw WrongLen(b.len, len, __func__);
		}
		BitArray r(b.size(), 0);
		for (int i = 0; i < r.size(); i++) {
			r.set(i, b[i] ^ (*this)[i]);
		}
		delete[] arr;
		arr = r.arr;
		len = r.len;
		return *this;
	}

	BitArray& operator<<=(int n) {
		BitArray tmp(len + n, 0);
		for (int i = 0; i < len; i++) {
			tmp.set(i+n, (*this)[i]);
		}
		delete[] arr;
		len = tmp.len;
		arr = tmp.arr;
		return *this;
	}
	BitArray& operator>>=(int n) {
		if (n > len - 1)
			throw WrongNum(n, __func__);
		BitArray tmp(len-n, 0);
		for (int i = len-n-1; i >= 0; i--) {
			tmp.set(i, (*this)[i + n]);
		}
		delete[] arr;
		arr = tmp.arr;
		len = tmp.len;
		return *this;
	}
	BitArray operator<<(int n) const {
		BitArray tmp(len + n, 0);
		for (int i = 0; i < len; i++) {
			tmp.set(i + n, (*this)[i]);
		}
		return tmp;
	}
	BitArray operator>>(int n) const {
		if (n > len - 1)
			throw WrongNum(n, __func__);
		BitArray tmp(len - n, 0);
		for (int i = len - n - 1; i >= 0; i--) {
			tmp.set(i, (*this)[i + n]);
		}
		return tmp;
	}
	friend bool operator==(const BitArray& a, const BitArray& b) {
		if (a.size() == b.size()) {
			for (int i = 0; i < a.size(); i++) {
				if (a[i] != b[i])
					return 0;
			}
			return 1;
		}
		return 0;
	}
	friend bool operator!=(const BitArray& a, const BitArray& b) {
		return (!(a == b));
	}
	friend BitArray operator&(const BitArray& b1, const BitArray& b2) {
		if (b1.len != b2.len)
			throw WrongLen(b1.len, b2.len, __func__);
		BitArray r(b1.size(), 0);
		for (int i = 0; i < r.size(); i++) {
			r.set(i, b1[i] & b2[i]);
		}
		return r;
	}
	friend BitArray operator|(const BitArray& b1, const BitArray& b2) {
		if (b1.len != b2.len)
			throw WrongLen(b1.len, b2.len, __func__);
		BitArray r(b1.size(), 0);
		for (int i = 0; i < r.size(); i++) {
			r.set(i, b1[i] | b2[i]);
		}
		return r;
	}
	friend BitArray operator^(const BitArray& b1, const BitArray& b2) {
		if (b1.len != b2.len)
			throw WrongLen(b1.len, b2.len, __func__);
		BitArray r(b1.size(), 0);
		for (int i = 0; i < r.size(); i++) {
			r.set(i, b1[i] ^ b2[i]);
		}
		return r;
	}

private:
	long len;
	long* arr = NULL;

};



#endif
