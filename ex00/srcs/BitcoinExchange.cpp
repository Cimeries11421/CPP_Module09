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
		if (str.size() > 10)
		{
			key = str.substr(0, 10);
			value = static_cast<float>(atof(str.substr(11, str.size() - 1).c_str()));
		}
		_base[key] = value;
	}
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
