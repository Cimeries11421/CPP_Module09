#ifndef	EXCHANGE_HPP
#define EXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

class	ErrorOpen : public std::exception
		{
			const char* what() const throw()
			{
				return ("File can't be open");
			}
		};


class	Exchange
{
	private :
		std::map<std::string, float>	_base;
		std::ifstream					_file;
		Exchange(const Exchange &other);
		Exchange	&operator=(const Exchange &other);
	
	public :
		Exchange();
		~Exchange();
		void		fillBase(void);
		std::string	findCloserDate(const std::string &key);
		float	operator[](const std::string &key);
		class	NoEquivalentDate : public std::exception
		{
			const char* what() const throw()
			{
				return ("There is no inferior or equivalent date");
			}
		};

		void	printBase(void);
};

#endif
