#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <string>
#include <stack>
#include <queue>

#include <iostream>

class Calculator
{
public:
	Calculator();

	double solve(std::string& in);

	void enableDebug();
	void disableDebug();

private:
	bool isDigit(char c);
	bool isOperator(char c);

	enum class TokenType
	{
		EMPTY,
		NUMBER,
		OPERATOR
	};

	struct Token
	{
		TokenType type;
		union {
			double value;
			char opCode;
		};
		Token();
		explicit Token(double value);
		explicit Token(char opCode);

	};

	std::queue<Token> tokenize(std::string& input);
	double calculate(std::queue<Token>& input);
	double doOperation(char op, double l, double r);
	bool isCurrentMorePowerful(char last, char current) const;
	constexpr int getOperatorPower(char op) const;
	void moveOperatorsUntilBracet(std::queue<Token>& out, std::stack<Token>& ops);

	void debugPrint(const std::queue<Token>& tokens) const;
	bool isDebugging;

	friend std::ostream& operator<<(std::ostream& os, const Calculator::Token& t);
};


inline std::ostream& operator<<(std::ostream& os, const Calculator::Token& t)
{
	if (t.type == Calculator::TokenType::NUMBER)
	{
		os << "NUM:" << t.value << std::endl;
	}

	else
	{
		os << "OP:" << t.opCode << std::endl;
	}
	return os;
}


#endif /* SRC_CALC_H_ */
