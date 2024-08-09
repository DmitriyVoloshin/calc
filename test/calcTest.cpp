#include "CppUTest/TestHarness.h"
#include <limits>

#include "../src/calc.h"

TEST_GROUP(CalcTest)
{
	Calculator* calc;
	std::string input {""};
	double result;

	void setup()
	{
		calc = new Calculator();
		result = 0;
	}

	void teardown()
	{
		delete calc;
	}
};

TEST(CalcTest, CanPassEmptyString)
{
	result = calc->solve(input);

	DOUBLES_EQUAL(0, result, 0.001);
}

TEST(CalcTest, CanPass1Value)
{
	for (int i = 0; i < 10; i++)
	{
		input = std::to_string(i);
		result = calc->solve(input);
		DOUBLES_EQUAL(i, result, 0.001);
	}
}

TEST(CalcTest, CanPassCombinedValue)
{
	for (int i = 0; i < 10; i++)
	{
		input = std::to_string(10 + i);
		result = calc->solve(input);
		DOUBLES_EQUAL(10 + i, result, 0.001);
	}
}

TEST(CalcTest, CanPassLongValue)
{
	int val = std::numeric_limits<int>::max();
	input = std::to_string(val);
	result = calc->solve(input);
	DOUBLES_EQUAL(val, result, 0.001);
}

TEST(CalcTest, CanPass1NegativeValue)
{
	for (int i = 0; i > -10; i--)
	{
		input = std::to_string(i);
		result = calc->solve(input);
		DOUBLES_EQUAL(i, result, 0.001);
	}
}


TEST(CalcTest, CanPassLongNegativeValue)
{
	int val = std::numeric_limits<int>::min();
	input = std::to_string(val);
	result = calc->solve(input);
	DOUBLES_EQUAL(val, result, 0.001);
}

TEST(CalcTest, CanAddOneDigitNumbers)
{
	input = "1+1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}
/*
TEST(CalcTest, CanAddOneDigitNumbersWithSpaces)
{
	input = "1 + 1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(CalcTest, CanAddOneDigitNumbersWithMultipleSpaces)
{
	input = "1  +    1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(CalcTest, CanAddOneDigitNumbersWithPrefixSpace)
{
	input = " 1+1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(CalcTest, CanAddOneDigitNumbersWithPrefixMultipleSpaces)
{
	input = "     1+1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(CalcTest, CanAddOneDigitNumbersWithPostfixSpace)
{
	input = "1+1 ";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(CalcTest, CanAddOneDigitNumbersWithPostfixMultipleSpaces)
{
	input = "1+1    ";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(CalcTest, CanAddOneDigitNumbersWithMultiplePrefixPostfixAndMidSpaces)
{
	input = "    1   + 1     ";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}*/



