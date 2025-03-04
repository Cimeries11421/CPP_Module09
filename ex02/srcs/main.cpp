#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <climits>
#include <ctime>

int	parseInput(int ac, char **av);

int	main(int ac, char **av)
{
	if (ac <= 1)
	{
		std::cerr << "need at least ONE argument" << std::endl;
		return (1);
	}
	if (parseInput(ac, av) == -1)
	{
		return (-1);
	}
	clock_t	start = clock();
	PmergeMe<std::vector<int>, std::vector<std::pair<int, int> > >container1(ac, av);
	std::cout << "Before : "; 
	container1.printList();
	container1.sortNbr(1);
	clock_t	end = clock();
	double	time = double(end - start) / CLOCKS_PER_SEC;
	
	std::cout << "After  : "; 
	container1.printList();
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::vector "
		<< time << " us" << std::endl;

	clock_t	start2 = clock();
	PmergeMe<std::deque<int>, std::deque<std::pair<int, int> > >container2(ac, av);
	container2.sortNbr(1);
	clock_t	end2 = clock();
	double	time2 = double(end2 - start2) / CLOCKS_PER_SEC;
	
	std::cout << "Time to process a range of " << ac - 1 << " elements with std::deque "
		<< time2 << " us" << std::endl;

	return (0);
}

int	parseInput(int ac, char **av)
{
	long	tmp_tab[ac - 1];

	for (int j = 1; j < ac; ++j)
	{
		for (size_t i = 0; i < strlen(av[j]); ++i)
		{
			if (av[j][i] < '0' || av[j][i] > '9')
			{
				std::cerr << "Wrong Input" << std::endl;
				return (-1);
			}
		}
		char *endstr;
		tmp_tab[j - 1] =  strtol(av[j], &endstr, 10);
		if (tmp_tab[j - 1] > INT_MAX)
		{
			std::cerr << "Wrong Input : int max limit reached" << std::endl;
			return (-1);
		}
	}
	for (int i = 0; i < ac - 1; ++i)
	{
		for (int j = 0; j < ac - 2; ++j)
		{
			if (i != j && tmp_tab[i] == tmp_tab[j])
			{
				std::cerr << "Wrong Input : can't have duplicate" << std::endl;
				return (-1);
			}
		}
	}
	return (0);
} 
