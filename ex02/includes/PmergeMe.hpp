#ifndef P_H
#define P_H

#include <vector>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iterator>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define YELLOW "\x1b[33m"
#define ORANGE "\x1b[38;2;255;165;0m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define LIGHT_CYAN "\x1b[96m"
#define LIGHT_BLUE "\x1b[94m"
#define PINK "\001\x1b[38;2;255;105;180m\002"
#define RESET "\001\x1b[0m\002"

template<typename T>
class	PmergeMe
{
	private :
		T	_listNbr;
		T	_main;
		T	_pend;
		T	_odd;
		//int	_level;

		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe	&operator=(const PmergeMe &other);

	public :
		PmergeMe(int ac, char **av);
		~PmergeMe();
		void	sortNbr(size_t lvl);
		void	swapPairs(size_t lvl, size_t x, size_t y);
		void	fillMainPendOdd(size_t lvl);
		void	insertIntoMain(size_t lvl);
		void	insertElementsIntoList(size_t lvl, int biggerValue, int value);

		void	printList(void);
		void	printMainPend(void);
};

#endif
