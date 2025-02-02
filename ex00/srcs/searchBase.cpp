#include "Exchange.hpp"
#include "utils.hpp"

static int	checkFormat(const std::string &str)
{
	for (unsigned long i = 0; i < str.size(); ++i)
	{
		if ((i == 4 || i == 7) && str[i] != '-')
			return (-1);
		if ((i == 10 || i == 12) && str[i] != ' ')
			return (-1);
		if (i == 11 && str[i] != '|')
			return (-1);
		else if (((i >= 0 && i < 4) || i == 5 || i == 6 || i == 8 || i == 9 || i >= 13)
				&& str[i] < '0' || str[i] > '9')
			return (-1);
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
	//checker premiere ligne
	while (getline(input, str))
	{
		if (str.size() < 14)
			std::cout << "Error: bad input => " << str << std::endl;
		date = str.substr(0, 10);
		if (checkFormat(str) == -1) //|| checkDate(date) == -1)
		{
			std::cout << "Error: bad input => " << str << std::endl;
			continue ;
		}
		closerDate = base.findCloserDate(date);
		nbrBits = atof(str.substr(13, str.size() - 1).c_str());
		if (nbrBits < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue ;
		}
		/*std::cout << "input file date : " << date;
		std::cout << " | " << nbrBits << std::endl;
		std::cout << "closerDate : "<< closerDate << " -> "<< base[closerDate] << std::endl;
		std::cout << "result : " << base[closerDate] * nbrBits << "\n" << std::endl;*/

		//affichage officiel
		std::cout << date << " => " << nbrBits << " = " << base[closerDate] * nbrBits << std::endl;
	}
}

/*static void parseDate(const std::string &date)
{
	
}*/
