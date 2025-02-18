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
			this->swapPairs(lvl, x , y);
        }
        x += lvl * 2;
        y += lvl * 2;
    }
	std::cout << GREEN << "PARTIE 1 -> level : " << lvl << RESET << std::endl;
    this->printList(); //enlever
	if (_listNbr.size() / (lvl * 2) >= 2) // taille /  next lvl > 2, alors capacite d'un autre.
		this->sortNbr(lvl * 2);	
	std::cout << BLUE << "PARTIE 2 -> level : " << lvl << RESET << std::endl;

	this->fillMainPendOdd(lvl);
	this->printMainPend(); // enlever
	this->insertIntoMain(lvl);
	
/*	 typename T::iterator	it_end = _listNbr.end();

	 while (it != it_end)*/
}

template<typename T>
void	PmergeMe<T>::swapPairs(size_t lvl, size_t x, size_t y)
{
	for (size_t count = 0; count < lvl; ++count)
    {
        std::swap(_listNbr[x - count], _listNbr[y - count]);
    }
}

template<typename T>
void	PmergeMe<T>::fillMainPendOdd(size_t lvl)
{
	size_t	x = lvl - 1;
	size_t	y = lvl * 2 - 1;
	size_t	i;

	_main.clear();
	_pend.clear();
	_odd.clear();
	_main.push_back(_listNbr[x]);
	while (y < _listNbr.size())
	{
		_main.push_back(_listNbr[y]);
		y += lvl * 2;
		if (x > lvl - 1)
			_pend.push_back(_listNbr[x]);
		x += lvl * 2;
	}
	i = x;
	while (i < _listNbr.size())
	{
		_odd.push_back(_listNbr[i]);
		i += lvl;
	}
}

//cherche ou mettre la valeur de pend dans le main et l'insere, puis pareil avec la vraie liste
//mais avec la paire associee.
template<typename T>
void	PmergeMe<T>::insertIntoMain(size_t lvl)
{
	typename T::iterator	posMain;
	size_t					i = 0;

	(void)lvl;
	while (i < _pend.size())
	{
		posMain = upper_bound(_main.begin(), _main.end(), _pend[i]);
		std::cout << ORANGE << "posMain = " << *posMain << RESET << std::endl;
		this->insertElementsIntoList(lvl, *posMain, _pend[i]);
		_main.insert(posMain, _pend[i]); 
	//	posList_x = find(_listNbr.begin(), _listNbr.end(), _pend[i]);
	//	y = distance(_listNbr.begin(), _listNbr.end(), *posMain) 
	//	x = distance(_listNbr.begin(), _listNbr.end(), *posMain) 
		++i;
	}
	std::cout << CYAN << "AFTER INSERTION" << RESET << std::endl;
	this->printMainPend();
//	this->printList();
}

//Cherche la paire du pend dans la liste a partie de la valeur, trouve ensuite sa future position 
//par la position du nombre superieur a la valeur, et echange les places des paires.
template<typename T>
void	PmergeMe<T>::insertElementsIntoList(size_t lvl, int biggerValue, int value)
{
	typename T::iterator	posValue;
	typename T::iterator	newPosValue;

	(void)lvl;
	posValue = find(_listNbr.begin(), _listNbr.end(), value);
	newPosValue = find (_listNbr.begin(), _listNbr.end(), biggerValue);
/*	x = distance(_listNbr.begin(), posValue);
	y = distance(_listNbr.begin(), newPosValue);
	std::cout << "x = " << x << " list[x] = " << value << std::endl;
	std::cout << "y = " << y << " list[y] = " << biggerValue << std::endl;*/

	std::cout << "pos value = " << *posValue << std::endl;
	std::cout << "new pos value = " << *newPosValue << std::endl;
	this->printList();
	for (size_t i = 1; i < lvl; ++i)
	{
		_listNbr.insert(newPosValue, *posValue);
		posValue++;
		_listNbr.erase(posValue);
		newPosValue++;
	}
//	_listNbr.insert(newPosValue - 1, value);
//	_listNbr.erase(posValue);

	//this->swapPairs(lvl, x, y);

	this->printList();
}

template<typename T>
void PmergeMe<T>::printList(void)
{
	std::cout << PINK << "ListNbr : ";
    for (size_t i = 0; i < _listNbr.size(); ++i)
    {
        std::cout << _listNbr[i] << " ";
    }
    std::cout << RESET << std::endl;
}

template<typename T>
void PmergeMe<T>::printMainPend(void)
{
	std::cout << "Main : ";
    for (size_t i = 0; i < _main.size(); ++i)
    {
        std::cout << _main[i] << " ";
    }
    std::cout << std::endl;

	std::cout << "Pend : ";
    for (size_t i = 0; i < _pend.size(); ++i)
    {
        std::cout << _pend[i] << " ";
    }
    std::cout << std::endl;

	std::cout << "Odd : ";
    for (size_t i = 0; i < _odd.size(); ++i)
    {
        std::cout << _odd[i] << " ";
    }
    std::cout << std::endl;
}



// Instanciation explicite pour std::vector<int>
template class PmergeMe<std::vector<int> >;
