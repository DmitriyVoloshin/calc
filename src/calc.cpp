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

	double number;
	bool wasBuildingNumber = false;

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
			outputQueue.emplace(number);
			wasBuildingNumber = false;
		}

		if (isOperator(c))
		{
			opStack.push(c);
		}
	}

	if (wasBuildingNumber)
	{
		outputQueue.emplace(number);
		wasBuildingNumber = false;
	}

	while (!opStack.empty())
	{
		Token tk{opStack.top()};
		outputQueue.push(tk);
		opStack.pop();
	}

	return outputQueue;
}

inline bool Calculator::isDigit(char in)
{
	return '0' <= in && in <= '9';
}

inline bool Calculator::isOperator(char c)
{
	return c == '+' || c == '-';
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
	}

	return 0;
}

void Calculator::enableDebug()
{
	isDebugging = true;
}

void Calculator::disableDebug()
{
	isDebugging = false;
}


