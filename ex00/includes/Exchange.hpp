#ifndef	EXCHANGE_HPP
#define EXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

class	Exchange
{
	private :
		std::map<std::string, float>	_base;
		std::ifstream					_file;
		Exchange();
		Exchange(const Exchange &other);
		Exchange	&operator=(const Exchange &other);
	
	public :
		Exchange(char *file);
		~Exchange();
		int	fillBase(void);
		int	checkDate(std::string &date);
		class	ErrorOpen : public std::exception
		{
			const char* what() const throw()
			{
				return ("File can't be open");
			}
		};
};

#endif
