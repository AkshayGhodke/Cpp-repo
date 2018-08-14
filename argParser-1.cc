/*
 * argParser.cc
 *
 *  Created on: Sep 13, 2017
 *      Author: akshay
 */

#include <iostream>
#include <string.h>

#include "argParser.h"

using namespace std;

argParser::argParser()
{
	setArgs(0, 0);
}

argParser::argParser(char **argv, int argc)
{
	setArgs(argv,argc);
}

argParser::~argParser()
{
}

void argParser::setArgs(char **argv, int argc)
{
	argArr = argv;
	count = argc;
}

void argParser::sortArgs()
{
	for (int i = 1; i < count; i++)
	{
		for (int j = 1; j < count; j++)
		{
			if (strcmp(argArr[i], argArr[j]) < 0)
			{
				argArr[0] = argArr[i];
				argArr[i] = argArr[j];
				argArr[j] = argArr[0];
			}
		}
	}
}

void argParser::parse(char **argv, int argc)
{
	setArgs(argv,argc);
	sortArgs();
}

void argParser::printArgs()
{
	for (int i = 1; i < count; i++)
	{
		cout << argArr[i] << " ";
	}
	cout << endl;
}
