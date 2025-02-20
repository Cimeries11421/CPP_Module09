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
	typename T::iterator	posValueB;
	typename T::iterator	posValueA;
	size_t					indexB;

	posValueB = find(_listNbr.begin(), _listNbr.end(), valueB);
	std::cout << MAGENTA << "VALUE A = " << valueA << RESET << std::endl; 
	posValueA = find(_listNbr.begin(), _listNbr.end(), valueA);
	std::cout << ORANGE << "valeur A dans liste = " << *posValueA << std::endl;
	posValueA -= lvl - 1;
	std::cout << "valeur debut pair de A dans liste = " << *posValueA << std::endl;
	std::cout << "valeur B = " << *posValueB << std::endl;

	indexB = distance(_listNbr.begin(), posValueB);
	std::cout << GREEN << "index B = " << indexB << std::endl;
	std::cout << GREEN << "Value index B = " << _listNbr[indexB]<<  std::endl;
	for (size_t i = 0; i < lvl; ++i)
	{
		this->printList();
		_listNbr.insert(posValueA, *posValueB);
	}
	std::cout << CYAN << "AFTER INSERTION" << RESET << std::endl;
	this->printList();

//	posValueB = find (_listNbr.begin() + indexB, _listNbr.end(), valueB); // pas sur du truc la ?? 
	posValueB = _listNbr.begin() + indexB + 1; // + 1 fout la merde non ?? 
	//std::cout << LIGHT_CYAN << "valeur de B après ajout de lvl = " << *posValueB << RESET <<std::endl;
	for (size_t i = 0; i < lvl; ++i)
	{
		std::cout << LIGHT_CYAN << "valeur de B après ajout de lvl = " << *posValueB << RESET <<std::endl;
		posValueB = _listNbr.erase(posValueB);
	}
	std::cout << CYAN << "AFTER INSERTION AND ERASE" << RESET << std::endl;
	this->printMainPend();
	this->printList();
	std::cout << "---------------------------------\n" << std::endl;

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
