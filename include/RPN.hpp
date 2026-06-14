#ifndef RPN_HPP_
#define RPN_HPP_

#include <stack>

void eval_operation(std::stack<bool> &operands, const char op);
void negation(std::stack<bool> &operands);
void conjunction(std::stack<bool> &operands);
void disjunction(std::stack<bool> &operands);
void exclusive_disjunction(std::stack<bool> &operands);
void material_condition(std::stack<bool> &operands);
void equivalence(std::stack<bool> &operands);

class InsufficientOperandsException : public std::exception {
  public:
	const char *what() const throw() {
		return "Error: Not enough operands on the stack.";
	}
};

class InvalidOperandException : public std::exception {
  public:
	const char *what() const throw() {
		return "Error: Token is not a valid single-digit integer (0-9).";
	}
};

class TooManyOperandsException : public std::exception {
  public:
	const char *what() const throw() {
		return "Error: Incomplete expression, too many operands left.";
	}
};

class EmptyOperationException : public std::exception {
  public:
	const char *what() const throw() { return "Error: Empty operation."; }
};

#endif /* RPN_HPP_ */
