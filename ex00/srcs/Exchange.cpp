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

void	Exchange::printBase(void)
{
	std::map<std::string, float>::iterator	it = _base.begin();
	std::map<std::string, float>::iterator	it_end = _base.end();
	while (it != it_end)
	{
		std::cout << 
	//	std::cout << it->first << " : "<< it->second <<  std::endl;
		++it;
	}
}

/*int	Exchange::fillBase(void)
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
}*/


