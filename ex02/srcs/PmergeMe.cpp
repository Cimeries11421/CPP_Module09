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
	size_t					indexA;
	size_t					i = 0;

	(void)lvl;
	while (i < _pend.size())
	{
		posMain = upper_bound(_main.begin(), _main.end(), _pend[i]);
		if (posMain == _main.end())
		{
			std::cout << "PAS DE PLUS GRAND" << std::endl;
			++i; // pose probleme ?  12 25 36 66 102
			continue ;
		}
		indexA = distance(_main.begin(), posMain);
		std::cout << "---------------------------------\n" << std::endl;
		std::cout << ORANGE << "valeur A dans main = " << *posMain << RESET << std::endl;
		std::cout << ORANGE << "position A dans main = " << indexA << RESET << std::endl;
		this->printMainPend();
		std::cout << RED << "valeur a inserer = " << _pend[i] << RESET <<std::endl;
		this->printList();
		this->insertElementsIntoList(lvl, *posMain, _pend[i]);
		std::cout << "---------------------------------\n" << std::endl;
		_main.insert(posMain, _pend[i]); 
		++i;
	}
	i = 0;
	this->printMainPend();
	this->printList();
	while (i < _odd.size())
	{
		posMain = upper_bound(_main.begin(), _main.end(), _odd[i]);
		if (posMain == _main.end())
		{
			std::cout << "PAS DE PLUS GRAND" << std::endl;
			++i; // pose probleme ?  12 25 36 66 102
			continue ;
		}
		indexA = distance(_main.begin(), posMain);
		std::cout  << "---------------------------------\n" << std::endl;
		std::cout << RED << "valeur A dans main = " << *posMain << RESET << std::endl;
		std::cout << RED << "position A dans main = " << indexA << RESET << std::endl;
		this->printMainPend();
		std::cout << RED << "valeur a inserer = " << _odd[i] << RESET <<std::endl;
		this->printList();
		this->insertElementsIntoList(lvl, *posMain, _odd[i]);
		_main.insert(posMain, _odd[i]); 
		++i;
	}
	this->printMainPend();
	this->printList();
}

//Cherche la paire du pend dans la liste a partie de la valeur, trouve ensuite sa future position 
//par la position du nombre superieur a la valeur, et echange les places des paires.
template<typename T>
void	PmergeMe<T>::insertElementsIntoList(size_t lvl, int valueA, int valueB)
{
	size_t	posA;
	size_t	posB;
	T		groupB(lvl);

	std::cout << GREEN << "valueA = " << valueA << RESET <<std::endl;
	std::cout << CYAN << "valueB = " << valueB << RESET <<std::endl;

	this->printList();
	for (size_t i = 0; i < _listNbr.size(); ++i)
	{
//		if (_listNbr[i] == valueA && (i + 1) % lvl == 0)
//			posA = i;
		if (_listNbr[i] == valueB && (i + 1) % lvl == 0)
			posB = i;
	}
	std::cout << CYAN << "posB = " << posB << RESET <<std::endl;
	size_t	groupB_start = posB - (lvl - 1);
	std::cout << CYAN << "groupB_start = " << groupB_start << RESET <<std::endl;
	for (size_t i = 0; i < lvl; ++i)
	{
		groupB[i] = _listNbr[groupB_start + i];
	}
	_listNbr.erase(_listNbr.begin() + groupB_start, _listNbr.begin() + groupB_start + lvl); //lvl 1 ? 

	for (size_t i = 0; i < _listNbr.size(); ++i)
	{
		if (_listNbr[i] == valueA && (i + 1) % lvl == 0)
			posA = i;
	}
	size_t	groupA_start = posA - (lvl - 1);
	
	_listNbr.insert(_listNbr.begin() + groupA_start, groupB.begin(), groupB.end());
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
