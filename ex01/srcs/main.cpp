#include "RPN.hpp"
#include <iostream>
#include <cstring>

int	main(int ac, char **av)
{
	RPN	stack;
	char	*str;

	if (ac != 2)
	{
		std::cout << "Need ONE argument" << std::endl;
		return (1);
	}
	str = av[1];
	for (size_t i = 0; i < strlen(str); ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
			stack.addNumberStak(&str[i]);
		else if (str[i] == '+')
			stack.sumNumbers();
		else if (str[i] == '-')
			stack.subtractNumbers();
		else if (str[i] == '*')
			stack.multiplyNumbers();
		else if (str[i] == '/')
			stack.divideNumbers();
	}
	std::cout << stack.returnResult() << std::endl;
}
