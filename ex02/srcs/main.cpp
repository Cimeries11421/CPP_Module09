#include "PmergeMe.hpp"
#include <iostream>
#include <vector>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "need ONE argument" << std::endl;
		return (1);
	}
	PmergeMe<std::vector<int> >	container1(av[1]);	
	container1.sortNbr(1);
}
