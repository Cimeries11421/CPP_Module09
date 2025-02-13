#include "PmergeMe.hpp"
#include <iostream>
#include <cstring>  // Pour strlen

template<typename T>
PmergeMe<T>::PmergeMe() {}

template<typename T>
PmergeMe<T>::PmergeMe(const PmergeMe<T> &other)
{
  (void)other; 
}

template<typename T>
PmergeMe<T>::PmergeMe(char *str)
{
	std::istringstream	flow(str);
	int					nbr;

    while (flow >> nbr)
    {
        _listNbr.push_back(nbr);
    }
}

template<typename T>
PmergeMe<T>::~PmergeMe() {}

template<typename T>
PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe<T> &other)
{
    if (this != &other)
    {
        _listNbr = other._listNbr;
        _main = other._main;
        _pend = other._pend;
        _odd = other._odd;
    }
    return *this;
}

template<typename T>
void PmergeMe<T>::sortNbr(size_t lvl)
{
    size_t x = lvl - 1;
    size_t y = lvl * 2 - 1;
    
	while (y < _listNbr.size())
    {
        if (_listNbr[y] < _listNbr[x])
        {
            for (size_t count = 0; count < lvl; ++count)
            {
                std::swap(_listNbr[x - count], _listNbr[y - count]);
            }
        }
        x += lvl * 2;
        y += lvl * 2;
    }
	std::cout << "PARTIE 1 -> level : " << lvl << std::endl;
    this->printList();
	if (lvl * 2 <= _listNbr.size())
		this->sortNbr(lvl * 2);	
	std::cout << "PARTIE 2 -> level : " << lvl << std::endl;
	
	x = lvl - 1;
	y = lvl * 2 - 1;
	_main.push_back(x);
	x += lvl * 2;
	while (y < _listNbr.size())
	{
		std::cout << "y = " << y << std::endl;
		_main.push_back(y);
		_pend.push_back(x);

		x += lvl * 2;
        y += lvl * 2;
	}
	this->printMainPend();
	
}

template<typename T>
void PmergeMe<T>::printList(void)
{
	std::cout << "ListNbr : ";
    for (size_t i = 0; i < _listNbr.size(); ++i)
    {
        std::cout << _listNbr[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void PmergeMe<T>::printMainPend(void)
{
	std::cout << "Main : ";
    for (size_t i = 0; i < _main.size(); ++i)
    {
        std::cout << _listNbr[i] << " ";
    }
    std::cout << std::endl;

	std::cout << "Pend : ";
    for (size_t i = 0; i < _pend.size(); ++i)
    {
        std::cout << _listNbr[i] << " ";
    }
    std::cout << std::endl;

}



// Instanciation explicite pour std::vector<int>
template class PmergeMe<std::vector<int> >;
