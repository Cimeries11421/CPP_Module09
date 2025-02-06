#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN	&RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		this->_stack = other._stack;
	}
	return (*this);
}

void	RPN::addNumberStack(const char *nbr)
{
	this->_stack.push(atoi(nbr));
}

void	RPN::sumNumbers(void)
{
	int	nbr;
	int	result;

	nbr = this->_stack.top();
	this->_stack.pop();
	result = this->_stack.top() + nbr;
	this->_stack.pop();
	this->_stack.push(result);
}

void	RPN::subtractNumbers(void)
{
	int	nbr;
	int	result;

	nbr = this->_stack.top();
	this->_stack.pop();
	result = this->_stack.top() - nbr;
	this->_stack.pop();
	this->_stack.push(result);
}

void	RPN::multiplyNumbers(void)
{
	int	nbr;
	int	result;

	nbr = this->_stack.top();
	this->_stack.pop();
	result = this->_stack.top() * nbr;
	this->_stack.pop();
	this->_stack.push(result);
}

void	RPN::divideNumbers(void)
{
	int	nbr;
	int	result;

	nbr = this->_stack.top();
	this->_stack.pop();
	result = this->_stack.top() / nbr;
	this->_stack.pop();
	this->_stack.push(result);
}

int	RPN::returnResult(void)
{
	return (this->_stack.top());
}
