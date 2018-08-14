/*
 * argParser.h
 *
 *  Created on: Sep 13, 2017
 *      Author: akshay
 */

#ifndef ARGPARSER_H_
#define ARGPARSER_H_


#include <iostream>

using namespace std;

class argParser{
private:
	int count;
	char **argArr;
	void sortArgs();
public:
	argParser();
	argParser(char **argv, int argc);
	~argParser();
	void printArgs();
	void setArgs(char **argv, int argc);
	void parse(char **argv, int argc);
};

#endif /* ARGPARSER_H_ */
