#include "Exchange.hpp"

Exchange::Exchange()
{
	_file.open("data.csv");
	if (_file.is_open() == false)
		throw ErrorOpen();
	else
		this->fillBase();
}

Exchange::Exchange(const Exchange &other)
{
	(void)other;
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

void	Exchange::fillBase(void)
{
	std::string	str;
	std::string	key;
	float		value;

	getline(this->_file, str);
	while (getline(this->_file, str))
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

void	Exchange::printBase(void)
{
	std::map<std::string, float>::iterator	it = _base.begin();
	std::map<std::string, float>::iterator	it_end = _base.end();
	while (it != it_end)
	{
		std::cout << it->first << " : "<< it->second <<  std::endl;
		++it;
	}
}
