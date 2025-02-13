#ifndef P_H
#define P_H

#include <vector>
#include <utility>
#include <cstdlib>
#include <sstream>

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
		PmergeMe(char *str);
		~PmergeMe();
		void	sortNbr(size_t lvl);
		void	printList(void);
		void	printMainPend(void);
};

#endif
