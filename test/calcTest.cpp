#include "CppUTest/TestHarness.h"
#include <limits>

#include "../src/calc.h"

TEST_GROUP(BasicOperations)
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

TEST(BasicOperations, CanPassEmptyString)
{
	result = calc->solve(input);

	DOUBLES_EQUAL(0, result, 0.001);
}

TEST(BasicOperations, CanPassZero)
{
	input = std::to_string(0);
	result = calc->solve(input);

	DOUBLES_EQUAL(0, result, 0.001);
}


TEST(BasicOperations, CanPass1Value)
{
	for (int i = 1; i < 10; i++)
	{
		input = std::to_string(i);
		result = calc->solve(input);
		DOUBLES_EQUAL(i, result, 0.001);
	}
}

TEST(BasicOperations, CanPassCombinedValue)
{
	for (int i = 0; i < 10; i++)
	{
		input = std::to_string(10 + i);
		result = calc->solve(input);
		DOUBLES_EQUAL(10 + i, result, 0.001);
	}
}

TEST(BasicOperations, CanPassLongValue)
{
	int val = std::numeric_limits<int>::max();
	input = std::to_string(val);
	result = calc->solve(input);
	DOUBLES_EQUAL(val, result, 0.001);
}

TEST(BasicOperations, CanPass1NegativeValue)
{
	for (int i = -1; i > -10; i--)
	{
		input = std::to_string(i);
		result = calc->solve(input);
		DOUBLES_EQUAL(i, result, 0.001);
	}
}


TEST(BasicOperations, CanPassLongNegativeValue)
{
	int val = std::numeric_limits<int>::min();
	input = std::to_string(val);
	result = calc->solve(input);
	DOUBLES_EQUAL(val, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbers)
{
	input = "1+1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(BasicOperations, CanAddMultipleDigintsFirstNumber)
{
	input = "99+1";
	result = calc->solve(input);
	DOUBLES_EQUAL(100, result, 0.001);
}

TEST(BasicOperations, CanAddMultipleDigintsSecondNumber)
{
	input = "1+100";
	result = calc->solve(input);
	DOUBLES_EQUAL(101, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbersWithSpaces)
{
	input = "1 + 1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbersWithMultipleSpaces)
{
	input = "1  +    1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbersWithPrefixSpace)
{
	input = " 1+1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbersWithPrefixMultipleSpaces)
{
	input = "     1+1";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbersWithPostfixSpace)
{
	input = "1+1 ";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbersWithPostfixMultipleSpaces)
{
	input = "1+1    ";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}

TEST(BasicOperations, CanAddOneDigitNumbersWithMultiplePrefixPostfixAndMidSpaces)
{
	input = "    1   + 1     ";
	result = calc->solve(input);
	DOUBLES_EQUAL(2, result, 0.001);
}


TEST(BasicOperations, CanSubstructOneDigitNumbers)
{
	input = "1-1";
	result = calc->solve(input);
	DOUBLES_EQUAL(0, result, 0.001);
}

TEST(BasicOperations, CanSubstructMultipleDigitNumbers)
{
	input = "100-1";
	result = calc->solve(input);
	DOUBLES_EQUAL(99, result, 0.001);
}

TEST(BasicOperations, CanAddMultipleNumbers)
{
	input = "1+1+35";
	result = calc->solve(input);
	DOUBLES_EQUAL(37, result, 0.001);
}

TEST(BasicOperations, CanAddFromNegativeNumber)
{
	input = "-1+8";
	result = calc->solve(input);
	DOUBLES_EQUAL(7, result, 0.001);
}

TEST(BasicOperations, CanSubstractMultipleNumbers)
{
	input = "99-1-1";
	result = calc->solve(input);
	DOUBLES_EQUAL(97, result, 0.001);
}

TEST(BasicOperations, CanSubstractnegativeNumbers)
{
	input = "-1-1";
	result = calc->solve(input);
	DOUBLES_EQUAL(-2, result, 0.001);
}

TEST(BasicOperations, CanMultiplyNumbers)
{
	input = "2*3";
	result = calc->solve(input);
	DOUBLES_EQUAL(6, result, 0.001);
}

TEST(BasicOperations, CanMultiplyByZero)
{
	input = "0*3";
	result = calc->solve(input);
	DOUBLES_EQUAL(0, result, 0.001);
}

TEST(BasicOperations, CanMultiplyFirstNegativeNumber)
{
	input = "-1*7";
	result = calc->solve(input);
	DOUBLES_EQUAL(-7, result, 0.001);
}

TEST(BasicOperations, CanMultiplySecondNegativeNumber)
{
	input = "1*-7";
	result = calc->solve(input);
	DOUBLES_EQUAL(-7, result, 0.001);
}

TEST(BasicOperations, CanMultiplyTwoNegativeNumbers)
{
	input = "-1*-7";
	result = calc->solve(input);
	DOUBLES_EQUAL(7, result, 0.001);
}

TEST(BasicOperations, CanDivideNumbers)
{
	input = "1/10";
	result = calc->solve(input);
	DOUBLES_EQUAL(0.1, result, 0.001);
}

TEST(BasicOperations, CanDivideNumbers2)
{
	input = "110/10";
	result = calc->solve(input);
	DOUBLES_EQUAL(11, result, 0.001);
}

TEST(BasicOperations, CanDivideNegativeFirstNumber)
{
	input = "-110/10";
	result = calc->solve(input);
	DOUBLES_EQUAL(-11, result, 0.001);
}

TEST(BasicOperations, CanDivideNegativeSecondNumber)
{
	input = "110/-10";
	result = calc->solve(input);
	DOUBLES_EQUAL(-11, result, 0.001);
}

TEST(BasicOperations, CanDivideNegativeNumbers)
{
	input = "-110/-10";
	result = calc->solve(input);
	DOUBLES_EQUAL(11, result, 0.001);
}



TEST_GROUP(Order)
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



TEST(Order, LastOperatorHasMorePower)
{
	input = "-1-7+5+2*9";
	result = calc->solve(input);
	DOUBLES_EQUAL(15, result, 0.001);
}


TEST(Order, MiddleOperatorHasMorePower)
{
	calc->enableDebug();
	input = "-7+5*2-7";
	result = calc->solve(input);
	DOUBLES_EQUAL(-4, result, 0.001);
}

TEST(Order, FirstOperatorHasMorePower)
{
	input = "-1*7+5+2-7";
	result = calc->solve(input);
	DOUBLES_EQUAL(-7, result, 0.001);
}



