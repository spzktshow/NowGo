#include "TypeConver.h"

namespace moonsugar 
{
	char * TypeConver::ConstCharToChar(const char * constChar)
	{
		size_t len = strlen(constChar);
		char * newChar = new char[len + 1];
		strcpy(newChar, constChar);
		return newChar;
	}

	char * TypeConver::StringToChar(std::string * str)
	{ 
		return ConstCharToChar(str->c_str());
	}

	std::string * TypeConver::CharToString(char * charStr)
	{
		std::string * str = new std::string(charStr);
		return str;
	}

	char * TypeConver::combinationChar(char * char1, char * char2)
	{
		size_t len = strlen(char1) + strlen(char2);
		char * valueChar = new char[len + 1];
		strcpy(valueChar, char1);
		strcat(valueChar, char2);
		return valueChar;
	}

	int TypeConver::CharToInt(const char * s)
	{
		int sign = 1;
		if (*s == '-')
		{
			sign = -1;
			s ++;
		}
		int num = 0;
		while(*s)
		{
			num = ((*s) - '0') + num * 10;
			s ++;
		}
		return num * sign;
	}
}
