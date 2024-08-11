#include "calc.h"

#include <iostream>

Calculator::Calculator() : isDebugging(false)
{}

Calculator::Token::Token() : type(TokenType::EMPTY), value(0)
{}

Calculator::Token::Token(double val) : type(TokenType::NUMBER), value(val)
{}

Calculator::Token::Token(char op) : type(TokenType::OPERATOR), opCode(op)
{}

double Calculator::solve(std::string& in)
{
	std::queue<Token> tokens = tokenize(in);

	if (tokens.empty())
		return 0;

	debugPrint(tokens);

	double result = calculate(tokens);

	return result;
}

std::queue<Calculator::Token> Calculator::tokenize(std::string& in)
{
	std::queue<Token> outputQueue;
	std::stack<char> opStack;
	char lastOp;

	double number;
	bool wasBuildingNumber = false;
	bool minusDetected = false;

	for (const auto c : in)
	{
		if (isDigit(c))
		{
			if (!wasBuildingNumber)
			{
				number = 0;
				wasBuildingNumber = true;
			}

			number *= 10;
			number += c - '0';
		}
		else if(wasBuildingNumber)
		{
			if (minusDetected)
			{
				number = -number;
				minusDetected = false;
			}
			outputQueue.emplace(number);
			wasBuildingNumber = false;
		}

		if (isOperator(c))
		{
			if (c == '-')
			{
				minusDetected = true;
			}
			else
			{
				if (!opStack.empty())
				{
					lastOp = opStack.top();
					if (getOperatorPower(lastOp) > getOperatorPower(c))
					{
						moveAllOperators(outputQueue, opStack);
					}
				}

				opStack.push(c);
			}
		}
	}

	if (wasBuildingNumber)
	{
		if (minusDetected)
		{
			number = -number;
			minusDetected = false;
		}
		outputQueue.emplace(number);
		wasBuildingNumber = false;
	}
	moveAllOperators(outputQueue, opStack);

	return outputQueue;
}

inline bool Calculator::isDigit(char in)
{
	return '0' <= in && in <= '9';
}

inline bool Calculator::isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}


void Calculator::moveAllOperators(std::queue<Token>& out, std::stack<char>& ops)
{
	while (!ops.empty())
	{
		out.emplace(ops.top());
		ops.pop();
	}
}

void Calculator::debugPrint(const std::queue<Token>& tokens) const
{
	if (isDebugging)
	{
		std::queue<Token> tokensToPrint = tokens;

		while(!tokensToPrint.empty())
		{
			Token t = tokensToPrint.front();
			tokensToPrint.pop();

			std::cout << t;
		}
		std::cout << "End of output\n\n";
	}
}

inline double Calculator::calculate(std::queue<Token>& input)
{
	std::stack<double> numbers;

	while (!input.empty())
	{
		Token t = input.front();
		if (t.type == TokenType::NUMBER)
		{
			numbers.push(t.value);
		}
		else
		{
			double right = numbers.top();
			numbers.pop();

			double left = 0;
			if (!numbers.empty())
			{
				left = numbers.top();
				numbers.pop();
			}

			double result = doOperation(t.opCode, left, right);
			numbers.push(result);
		}
		input.pop();
	}

	while(numbers.size() != 1)
	{
		double right = numbers.top();
		numbers.pop();

		double left = 0;
		if (!numbers.empty())
		{
			left = numbers.top();
			numbers.pop();
		}
		double result = doOperation('+', left, right);
		numbers.push(result);
	}


	return numbers.top();
}

double Calculator::doOperation(char op, double l, double r)
{
	switch (op)
	{
		case '-':
			return l - r;
		case '+':
			return l + r;
		case '*':
			return l * r;
		case '/':
			return l / r;
	}

	return 0;
}

constexpr int Calculator::getOperatorPower(char op)
{
	switch (op)
	{
		case '-' :
		case '+':
			return 1;
		case '*':
		case '/':
			return 2;

		default:
			return 100;
	}
}

void Calculator::enableDebug()
{
	isDebugging = true;
}

void Calculator::disableDebug()
{
	isDebugging = false;
}


