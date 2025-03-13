#include "BitcoinExchange.hpp"

static int	checkFormat(const std::string &str);
static int	checkDate(const std::string &date);
void	searchBase(char	*inputFile, Exchange &base);

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	if (ac != 2)
	{
		std::cout << "Error: need 1 file" << std::endl;
		return (1);
	}
	try
	{
		Exchange	base("data.csv");
		searchBase(av[1], base);
	}
	catch (std::exception &ref)
	{
		std::cout << ref.what() << std::endl;
	}
	return (0);
}

void	searchBase(char	*inputFile, Exchange &base)
{
	std::ifstream	input;
	std::string		str;
	std::string		closerDate;
	std::string		date;
	float			nbrBits;

	input.open(inputFile);
	if (input.is_open() == false)
		throw	ErrorOpen();
	getline(input,str);
	if (str != "date | value")
		std::cout << "Error: first line syntax not valid." << std::endl;
	while (getline(input, str))
	{
		if (str.empty() == true)
			continue;
		if (str.size() < 14 || checkFormat(str) == -1)
		{
			std::cout << "Error: bad input => " << str << std::endl;
			continue;
		}
		date = str.substr(0, 10);
		if (checkDate(date) == -1)
		{
			std::cout << "Error: bad input => " << str << std::endl;
			continue;
		}
		closerDate = base.findCloserDate(date);
		nbrBits = atof(str.substr(13, str.size() - 1).c_str());
		if (nbrBits > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		if (nbrBits < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		std::cout << date << " => " << nbrBits << " = " << base[closerDate] * nbrBits << std::endl;
	}
	input.close();
}

static int	checkFormat(const std::string &str)
{
	unsigned long i = 0;
	bool	dot = false;

	(void)dot;
	while (i < 14)
	{
		if ((i == 4 || i == 7) && str[i] != '-')
			return (-1);
		if ((i == 10 || i == 12) && str[i] != ' ')
			return (-1);
		if (i == 11 && str[i] != '|')
			return (-1);
		if ((i < 4 || i == 5 || i == 6 || i == 8 || i == 9 || i == 13) && (str[i] < '0' || str[i] > '9'))
			return (-1);
		++i;
	}
	while (i < str.size())
	{
		if (str[i] == '.' && dot == false)
			dot = true;
		else if (str[i] == '.' && dot == true)
			return (-1);
		if (str[i] != '.' && (str[i] < '0' || str[i] > '9'))
			return (-1);
		++i;
	}
	return (0);
}

static int	checkDate(const std::string &date)
{
	int	year = atoi(date.substr(0, 4).c_str());
	int	month = atoi(date.substr(5, 7).c_str());
	int	day = atoi(date.substr(8, 10).c_str());

	if (year <= 2009 || ( year == 2009 && month == 1 && day < 2))
		return (-1);
	if (month > 12)
		return (-1);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (-1);
	if (day > 31)
		return (-1);
	if (month == 2 && year % 4 != 0 && day > 28)
		return (-1);
	if (month == 2 && day > 29)
		return (-1);
	return (-0);
}
