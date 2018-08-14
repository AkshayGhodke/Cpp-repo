//============================================================================
// Name        : myLISA.cpp
// Author      : Akshay Ghodke
// Version     : Testing
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace std;

int main() {
	const string FILE_NAME = "mytestdata.txt";
	const int COUNT = 1024;

	// generating an input file

	ofstream outputFile(FILE_NAME.c_str(), ios::binary | ios::trunc);

	// 1) Below code is for generating initial random bits before the sync field
	// This might not work as expected in case we find the buffer in the randomly generated bits

	/*int count_random_bits = COUNT - 32 * 8;
	 count_random_bits = rand() % count_random_bits;
	 srand(time(NULL));

	 for (int i = 0; i < count_random_bits; i++) {
	 int random_bits;
	 random_bits = rand() % 2;
	 cout << random_bits;
	 outputFile << random_bits;
	 }*/

	// 2) Manually generating random bits which won't contain any "0101" or "1010"
	// to enable 1) comment the below two code lines.

	string random_bits =
			"01111111110111111111110110111011111111110111011111111111101111111011111111101100000110011011001111111111101111011111111101110111111111111111111110000000000000000000000111111111111111111100000011111111111111110000000000000000000000001111111111111111111000001111111111111110000000000000001111111111111000000000001111111111110110110011000111000001111111000001111111110000000000000011011111111111111100000000000000000000000000000000000000000000000111110111111111011101110011000011101111101111110111111111011111111111100000000000000000010000000000000000000000111111111111110000001100000000000000000011111111111111111111110000000000000111111111110000000000111111111111101111011100000001100001101111000000000000";
	outputFile << random_bits;

	string sync_field =
			"0101000001010001010100100101001101010100010101010101011001010111010110000101100101011010010110110101110001011101010111100101111110100000101000011010001010100011101001001010010110100110101001111010100010101001101010101010101110101100101011011010111010101111";

	// Code for altering the sync field bits according to corruption percentage

	float corruption_percent;

	cout << "Enter the sync field corruption Percentage: " << endl;
	cin >> corruption_percent;

	int corruption_bits; 	// no of bits to be corrupted

	corruption_bits = corruption_percent * 32 * 8 / 100;

	cout << corruption_percent << endl;

	for (int j = 0; j < corruption_bits; j++) {
		int sync_field_rand_pos = rand() % 256;

		if (sync_field.at(sync_field_rand_pos) == 1)
			sync_field.at(sync_field_rand_pos) = 0;
		else {
			sync_field.at(sync_field_rand_pos) = 1;
		}
		cout << "altered bits" << sync_field_rand_pos << endl;
	}

	string payload;

	// Ask's the usr for payload

	cout << "Enter the Message to print :" << endl;
	cin >> payload;

	string file_data = sync_field + payload;

	outputFile << file_data;
	outputFile.close();

	// Reading from input file to an array

	int buffer;
	int conf_level;

	ifstream input;
	char x;
	int arr[1024];
	int counter = 0;
	cout << "Enter buffer : " << endl;
	cin >> hex >> buffer;

	input.open(FILE_NAME.c_str(), ios::binary);

	if (input.fail()) {
		cout << "Failed to open " << FILE_NAME << endl;
		return -1;
	}

	input.read(&x, 1);
	cout << x << endl;

	do {
		if (x == 48) {
			arr[counter] = 0;
		} else if (x == 49) {
			arr[counter] = 1;
		}
		cout << "x : " << x << " arr " << arr[counter] << endl;
		counter++;
	} while (input >> x && counter < 1024);

	cout << "Enter Confidence Level :" << endl;
	cin >> conf_level;

	int i, j, k, current_window;
	int flag = false;
	int count_conf = 0;
	bool temp[8];

	for (i = 0; i < COUNT - 7; i++) {
		temp[0] = arr[i];
		temp[1] = arr[i + 1];
		temp[2] = arr[i + 2];
		temp[3] = arr[i + 3];
		temp[4] = arr[i + 4];
		temp[5] = arr[i + 5];
		temp[6] = arr[i + 6];
		temp[7] = arr[i + 7];

		current_window = temp[0] * pow(2, 7) + temp[1] * pow(2, 6)
				+ temp[2] * pow(2, 5) + temp[3] * pow(2, 4)
				+ temp[4] * pow(2, 3) + temp[5] * pow(2, 2)
				+ temp[6] * pow(2, 1) + temp[7] * pow(2, 0);

		k = temp[0] * pow(2, 3) + temp[1] * pow(2, 2) + temp[2] * pow(2, 1)
				+ temp[3] * pow(2, 0);

		j = temp[4] * pow(2, 3) + temp[5] * pow(2, 2) + temp[6] * pow(2, 1)
				+ temp[7] * pow(2, 0);

		cout << temp[0] << temp[1] << temp[2] << temp[3] << temp[4] << temp[5]
				<< temp[6] << temp[7] << endl;
		cout << " lower : " << j << " upper : " << k << " i : " << i
				<< " buffer : " << buffer << endl;

		// checks if the buffer matches the current window
		if (current_window == buffer) {
			flag = true;
			count_conf++;
			if (conf_level == count_conf) {
				break;
			} else {
				i = i + 7;
				if (buffer == 95) {
					buffer = 160;
				} else {
					buffer++;
				}
			}
		} else if (flag) {
			buffer++;
		}
	}

	int flag1 = true;
	if (k == 5) {
		i = i + ((32 - j) * 8);
	} else if (k == 10) {
		i = i + ((16 - j) * 8);
	} else {
		flag1 = false;
		cout << "No match found" << endl;
	}
	if (flag1) {
		for (int k = i; k < COUNT; k++) {
			if (arr[k] == 0 || arr[k] == 1) {
				cout << arr[k];
			}
		}
		cout << endl;
	}

	input.close();

	return 0;
}
