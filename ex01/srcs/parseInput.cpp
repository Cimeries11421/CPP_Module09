#include "RPN.hpp"

int	parseInput(const std::string &str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (i == '1' && (str.at(i) < '0' || str.at(i) > '9'))
			return (-1);
		if (str.at(i) != '1' && i % 2 != 0 && (str.at(i) != '+' && str.at(i) != '-' && str.at(i) != '*' && str.at(i) != '/'))
			return (-1);
		if (i % 2 == 0 && (str.at(i) < '0' || str.at(i) > '9'))
			return (-1);
	}
	return (0);
}
