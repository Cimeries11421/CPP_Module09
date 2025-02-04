#include "Exchange.hpp"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

//	base.printBase(); //a enlever
	if (ac != 2)
	{
		std::cout << "Error: need 2 arguments" << std::endl;
		return (1);
	}
	try
	{
		Exchange	base;
		searchBase(av[1], base);
	}
	catch (std::exception &ref)
	{
		std::cout << ref.what() << std::endl;
	}
	return (0);
}
