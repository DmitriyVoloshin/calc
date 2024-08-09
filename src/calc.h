#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <string>
#include <stack>

class Calculator
{
public:
	double solve(std::string& in);


private:
	enum class Type
	{
		NONE,
		DIGIT,
		OPERATION
	};

	struct Term
	{
		Type type;
		double value;
	};

	std::stack<Term> stack;
};




#endif /* SRC_CALC_H_ */
