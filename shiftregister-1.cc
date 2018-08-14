//============================================================================
// Name        : shiftregister.cpp
// Author      : Akshay Ghodke
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <getopt.h>
#include <vector>
#include <cstdlib>
#include <locale>

using namespace std;

class shiftregister {
public:
	shiftregister();
	~shiftregister();
	int setValues(string i_value);
	int setSize(char *size);
	int appendZero(int count);
	int shiftRight(char *shift_bits);
	int shiftLeft(char *shift_bits);
	int fillVacate(char *v);
	int print();
private:
	vector<char> initial_value;
	unsigned int size;
	unsigned int shift_bits;
	bool flag;
	bool flag1;
};

shiftregister::shiftregister() {
	size = 0;
	shift_bits = 0;
	flag = false;
	flag1 = false;
}

shiftregister::~shiftregister() {

}

int shiftregister::setValues(string v) {
	initial_value.clear();
	if (!flag1) {
		size = v.size();
	}

	if (size >= v.size()) {
		for (unsigned int i = 0; i < v.size(); i++) {
			char c = v.at(i);
			if (c == '0' || c == '1') {
				initial_value.push_back(c);
			} else {
				return -1;
			}
		}
		appendZero(size - initial_value.size());
	} else {
		return -1;
	}
	return 0;
}

int shiftregister::appendZero(int count) {
	for (int i = 0; i < count; i++) {
		initial_value.insert(initial_value.begin(), '0');
	}
	return 0;
}

int shiftregister::setSize(char *length) {
	flag1 = true;
	size = atoi(length);
	if (size > initial_value.size()) {
		appendZero(size - initial_value.size());
	} else {
		return -1;
	}
	return 0;

}
int shiftregister::shiftRight(char *bit) {
	flag = true;
	shift_bits = atoi(bit);

	if (shift_bits <= initial_value.size()) {
		if (shift_bits != 0) {
			for (unsigned int i = initial_value.size() - 1; i >= shift_bits;
					i--) {
				initial_value.at(i) = initial_value.at(i - shift_bits);
			}
			for (unsigned int i = 0; i < shift_bits; i++) {
				initial_value.at(i) = '0';
			}
		}
	} else {
		return -1;
	}
	return 0;
}

int shiftregister::shiftLeft(char *bit) {
	flag = false;
	shift_bits = atoi(bit);
	if (shift_bits <= initial_value.size()) {
		if (shift_bits != 0) {
			for (unsigned int i = 0; i < initial_value.size() - shift_bits;
					i++) {
				initial_value.at(i) = initial_value.at(i + shift_bits);
			}
			for (unsigned int i = initial_value.size() - shift_bits;
					i < initial_value.size(); i++) {
				initial_value.at(i) = '0';
			}
		}
	} else {

		return -1;
	}
	return 0;
}

int shiftregister::fillVacate(char *v) {
	if (v[0] == '0' || v[0] == '1') {
		if (flag) {
			for (unsigned int i = 0; i < shift_bits; i++) {
				initial_value.at(i) = v[0];
			}
		} else {
			for (unsigned int i = initial_value.size() - shift_bits;
					i < initial_value.size(); i++) {
				initial_value.at(i) = v[0];
			}
		}
	} else {
		return -1;
	}
	return 0;
}

int shiftregister::print() {
	if (initial_value.size() != 0) {
		for (unsigned int i = 0; i < initial_value.size(); i++) {
			cout << initial_value.at(i);
		}
		cout << endl;
		return 0;
	} else {
		return -1;
	}
}

int main(int a, char* args[]) {

	int s = 0;
	int e = 0;

	shiftregister r1;

	vector<string> value;

	while ((s = getopt(a, args, "i:s:l:r:v:p")) != -1 && (e != -1))
		switch (s) {
		case 'i':
			e = r1.setValues(optarg);

			break;
		case 's':
			e = r1.setSize(optarg);
			break;
		case 'l':
			if (isdigit(optarg[0])) {
				e = r1.shiftLeft(optarg);
			} else {
				e = -1;
			}
			break;
		case 'r':
			if (isdigit(optarg[0])) {
				e = r1.shiftRight(optarg);
			} else {
				e = -1;
			}
			break;
		case 'v':
			e = r1.fillVacate(optarg);

			break;
		case 'p':
			e = r1.print();

			break;
		case '?':
			e = -1;
			break;
		default:
			e = -1;
			break;
		}

	return e;
}

