/*
 * TwoWayMap.cc
 *
 *  Created on: Sep 21, 2017
 *      Author: akshay
 */
#include <iostream>
#include "TwoWayMap.h"

using namespace std;

TwoWayMap::TwoWayMap()
{
	s_value = "";
	s_key = "";
	i_value = 0;
	i_key = 0;
}

bool TwoWayMap::setMapEntry(string key, int value)
{

	if (getMapValue(value) != "" || getMapValue(key) != 0)
	{
		string s_key = getMapValue(value);
		int i_key = getMapValue(key);

		i_map.erase(value);
		s_map.erase(key);
		i_map.erase(i_key);
		s_map.erase(s_key);

		s_map[key] = value;
		i_map[value] = key;
		return true;
	}
	else
	{
		s_map[key] = value;
		i_map[value] = key;
		return false;
	}
}

bool TwoWayMap::setMapEntry(int key, string value)
{
	if (getMapValue(key) != " " || getMapValue(value) != 0)
	{
		string s_key = getMapValue(key);
		int i_key = getMapValue(value);

		i_map.erase(key);
		s_map.erase(value);
		i_map.erase(i_key);
		s_map.erase(s_key);

		i_map[key] = value;
		s_map[value] = key;
		return true;
	}
	else
	{
		i_map[key] = value;
		s_map[value] = key;
		return false;
	}
}

string TwoWayMap::getMapValue(int key)
{
	s_value = i_map[key];
	return s_value;
}

int TwoWayMap::getMapValue(string key)
{
	i_value = s_map[key];
	return i_value;
}
