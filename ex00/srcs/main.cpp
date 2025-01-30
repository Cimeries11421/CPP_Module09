#include "Exchange.hpp"

int main(int ac, char **av)
{
	(void)ac;
	try
	{
		Exchange	base(av[1]);
		if (base.fillBase() == -1)
			return (-1);
	}
	catch (std::exception &ref)
	{
		std::cout << ref.what() << std::endl;
	}
	return (0);
}
