#include "calc.h"

double Calculator::solve(std::string& in)
{
	//using Calculator::Type;

	double accumulator = 0;

	double adding = 0;
	bool isNegative = false;

	//Type lastInput = Type::NONE;

	for (const auto& c : in)
	{
		if ('0' <= c && c <= '9')
			adding = c - '0';
		{
			if (accumulator != 0)
			{
				accumulator *= 10;
			}
			accumulator += adding;
		}
		if (c == '-')
		{
			isNegative = true;
		}
	}

	if(isNegative) accumulator = -accumulator;

	return accumulator;
}
