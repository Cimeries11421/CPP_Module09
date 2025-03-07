#include "RPN.hpp"
#include <iostream>
#include <cstring>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Need ONE argument" << std::endl;
		return (1);
	}
	RPN	stack;
	std::string	str(av[1]);
	
	if (parseInput(str) == -1)
	{
		std::cerr << "Wrong Input" << std::endl;
		return (1);
	}
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] >= '0' && str[i] <= '9')
			stack.addNumberStack(&str[i]);
		else if (str[i] == '+')
			stack.sumNumbers();
		else if (str[i] == '-')
			stack.subtractNumbers();
		else if (str[i] == '*')
			stack.multiplyNumbers();
		else if (str[i] == '/')
		{
			try 
			{
				stack.divideNumbers();
			}
			catch (std::exception &ref)
			{
				std::cout << ref.what() << std::endl;
				return (1);
			}
		}
	}
	std::cout << stack.returnResult() << std::endl;
	return (0);
}
