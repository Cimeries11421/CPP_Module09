#include "Exchange.hpp"

Exchange::Exchange() {}

Exchange::Exchange(char *file)
{
	std::string	str;
	std::string	key;
	std::cout << file << std::endl;
	_file.open(file);
	if (_file.is_open() == false)
		throw ErrorOpen();
}

Exchange::Exchange(const Exchange &other)
{
	(void)other;
}

int	Exchange::fillBase(void)
{
	std::string	str;
	std::string	key;

	getline(this->_file, str);
	while (getline(this->_file, str))
	{
		//continue ;
		if (str.size() < 11)
			return (-1);
		key = str.substr(0, 11);
		std::cout << "key = " << key << std::endl;
		if (this->checkDate(key) == -1)
		{
			std::cout << "Error : Wrong date" << std::endl;
			return (-1);
		}
	}
	return (0);
}

int	Exchange::checkDate(std::string &date)
{
	int	year;
	int	month;
	int	day;

	if (date[10] != ',')
			return (-1);
	year = atoi((date.substr(0, 3)).c_str());
	month = atoi((date.substr(5, 6)).c_str());
	day = atoi((date.substr(8, 9)).c_str());
	if (year < 2008 || year > 2025) //|| (year == 2025 && month > 2)) // a tester
	{
		std::cout << "par la" << std::endl;
		return (-1);
	}
	if (month < 1 || month > 12)
	{
		std::cout << "par la" << std::endl;
		return (-1);
	}
	if (day > 30) // a revoir
		return (-1);
	return (0);
}

Exchange	&Exchange::operator=(const Exchange &other)
{
	if (this != &other)
	{
		return (*this);
	}
	return (*this);
}

Exchange::~Exchange() {}
