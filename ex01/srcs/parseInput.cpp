#include "RPN.hpp"
#include <iostream>

int	parseInput(const std::string &str)
{
	size_t	i = 0;
	int count_nbr = 0;
	int count_op = 0;

	while (str[i] == ' ')
		++i;
	while (i < str.size())
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/'
				&& str[i] != ' ')
			return (-1);
		if (str[i] >= '0' && str[i] <= '9')
		{
			count_nbr++;
		}
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			count_op++;
		}
		if (count_op >= count_nbr)
			return (-1);
		++i;
	}
	count_nbr -= count_op;
	if (count_nbr != 1)
		return (-1);
	return (0);
}
