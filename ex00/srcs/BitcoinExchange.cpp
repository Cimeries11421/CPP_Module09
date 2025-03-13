#include "BitcoinExchange.hpp"

Exchange::Exchange(const std::string &file_str)
{
	std::ifstream	file;
	file.open(file_str.c_str());
	if (file.is_open() == false)
	{
		std::cout << "Need data.csv" << std::endl;
		throw ErrorOpen();
	}
	else
		this->fillBase(file);
	file.close();
}

Exchange::Exchange(const Exchange &other)
{
	*this = other;
}

Exchange	&Exchange::operator=(const Exchange &other)
{
	if (this != &other)
	{
		_base = other._base;
		return (*this);
	}
	return (*this);
}

Exchange::~Exchange() {}

void	Exchange::fillBase(std::ifstream &file)
{
	std::string	str;
	std::string	key;
	float		value;

	getline(file, str);
	while (getline(file, str))
	{
		if (isLineValid(str) == false)
			std::cout << "Error : INVALIDE LINE" << std::endl;
			//return (-1);
		if (str.size() > 10)
		{
			key = str.substr(0, 10);
			value = static_cast<float>(atof(str.substr(11, str.size() - 1).c_str()));
		}
		_base[key] = value;
	}
}

bool	Exchange::isLineValid(std::string str)
{
	size_t	i;
	bool	dot = false;

	if (str.size() < 12)
		return (false);
	while (i < 12)
	{
		if ((i == 4 || i == 7) && str[i] != '-')
			return (-1);
		if (i == 10 && str[i] != ',')
			return (-1);
		if ((i < 4 || i == 5 || i == 6 || i == 8 || i == 9 || i == 11) && (str[i] < '0' || str[i] > '9'))
			return (-1);
		++i;
	}
	while (i < str.size())
	{
		if (str[i] == '.' && dot == false)
			dot = true;
		else if (str[i] == '.' && dot == true)
			return (false);
		if (str[i] != '.' && (str[i] < '0' || str[i] > '9'))
			return (false);
		++i;
	}
	return (true);
}

//renvoie la plus grande date - 1 pour avoir l'inferieur ou l'egale
std::string	Exchange::findCloserDate(const std::string &key)
{
	std::map<std::string, float>::iterator	posDate;

	posDate = _base.upper_bound(key);
	if (posDate != _base.begin())
		--posDate;
	return (posDate->first);
}

float	Exchange::operator[](const std::string &key)
{
	return (_base[key]);
}
