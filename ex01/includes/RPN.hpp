#ifndef RPN_H
#define RPN_H

#include <stack>
#include <cstdlib>
#include <string>
#include <stdexcept>

int	parseInput(const std::string &str);

class	RPN
{
	private :
		std::stack<int>	_stack;
	public :
		RPN();
		~RPN();
		RPN(const RPN &other);
		RPN	&operator=(const RPN &other);
		void	addNumberStack(const char *nbr);
		void	sumNumbers(void);
		void	subtractNumbers(void);	
		void	multiplyNumbers(void);	
		void	divideNumbers(void);
		int		returnResult(void);
};

#endif
