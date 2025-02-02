#include "Exchange.hpp"
#include "utils.hpp"

int main(int ac, char **av)
{
	Exchange	base;
	(void)ac;
	(void)av;

	base.printBase(); //a enlever
	try
	{
		searchBase(av[1], base);
	}
	catch (std::exception &ref)
	{
		std::cout << ref.what() << std::endl;
	}


	return (0);
}
