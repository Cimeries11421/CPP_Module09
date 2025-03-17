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
				return ("Error : File can't be open");
			}
		};

class	Exchange
{
	private :
		std::map<std::string, float>	_base;

		Exchange();
		Exchange(const Exchange &other);
		Exchange	&operator=(const Exchange &other);
	
	public :
		Exchange(const std::string &file);
		~Exchange();
		void		fillBase(std::ifstream &file);
		std::string	findCloserDate(const std::string &key);
		float		operator[](const std::string &key);
		class	NoEquivalentDate : public std::exception
		{
			const char* what() const throw()
			{
				return ("There is no inferior or equivalent date");
			}
		};
};

void	searchBase(char	*inputFile, Exchange &base);

#endif
