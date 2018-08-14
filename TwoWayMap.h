/*
 * TwoWayMap.h
 *
 *  Created on: Sep 21, 2017
 *      Author: akshay
 */

#ifndef TWOWAYMAP_H_
#define TWOWAYMAP_H_

#include <iostream>
#include <map>

using namespace std;

class TwoWayMap
{
private:
	string s_value;
	string s_key;
	int i_value;
	int i_key;
	std::map<int, string> i_map;
	std::map<string, int> s_map;

public:
	TwoWayMap();

	bool setMapEntry(string, int);

	bool setMapEntry(int, string);

	string getMapValue(int);

	int getMapValue(string);
};

#endif /* TWOWAYMAP_H_ */
