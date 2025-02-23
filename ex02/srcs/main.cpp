#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

int	parseInput(int ac, char **av);

int	main(int ac, char **av)
{
	if (ac < 1)
	{
		std::cerr << "need at least ONE argument" << std::endl;
		return (1);
	}
	if (parseInput(ac, av) == -1)
	{
		std::cerr << "Wrong input" << std::endl;
		return (-1);
	}
	PmergeMe<std::vector<int> >container1(ac, av);	
	container1.sortNbr(1);
	container1.printList();
	return (0);
}

int	parseInput(int ac, char **av)
{
	long nbr;
	for (int j = 1; j < ac; ++j)
	{
		for (size_t i = 0; i < strlen(av[j]); ++i)
		{
			if (av[j][i] < '0' || av[j][i] > '9')
			{
				return (-1);
			}
		}
		char *endstr;
		nbr = strtol(av[j], &endstr, 10);
		if (nbr > INT_MAX)
		{
			std::cout << "int max limit reached" << std::endl;
			return (-1);
		}
	}
	return (0);
} 
