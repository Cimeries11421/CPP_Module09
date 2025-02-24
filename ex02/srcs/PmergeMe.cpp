#include "PmergeMe.hpp"
#include <iostream>
#include <cstring>  // Pour strlen

template<typename T, typename Tpair>
PmergeMe<T, Tpair>::PmergeMe() {}

template<typename T, typename Tpair>
PmergeMe<T, Tpair>::PmergeMe(const PmergeMe<T, Tpair> &other)
{
  (void)other; 
}

template<typename T, typename Tpair>
PmergeMe<T, Tpair>::PmergeMe(int ac, char **av)
{
	for (int i = 1; i < ac; ++i)
	{
		_listNbr.push_back(atoi(av[i]));
	}
}

template<typename T, typename Tpair>
PmergeMe<T, Tpair>::~PmergeMe() {}

template<typename T, typename Tpair>
PmergeMe<T, Tpair>& PmergeMe<T, Tpair>::operator=(const PmergeMe<T, Tpair> &other)
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

template<typename T, typename Tpair>
void PmergeMe<T, Tpair>::sortNbr(size_t lvl)
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
	if (_listNbr.size() / (lvl * 2) >= 2) // taille /  next lvl > 2, alors capacite d'un autre.
		this->sortNbr(lvl * 2);	
	this->fillMainPendOdd(lvl);
	this->insertIntoMain(lvl);
}

template<typename T, typename Tpair>
void	PmergeMe<T, Tpair>::swapPairs(size_t lvl, size_t x, size_t y)
{
	for (size_t count = 0; count < lvl; ++count)
    {
        std::swap(_listNbr[x - count], _listNbr[y - count]);
    }
}

template<typename T, typename Tpair>
void	PmergeMe<T, Tpair>::fillMainPendOdd(size_t lvl)
{
	size_t	x = lvl - 1;
	size_t	y = lvl * 2 - 1;
	size_t	i;

	_main.clear();
	_pend.clear();
	_odd.clear();
	_main.push_back(_listNbr[x]);
	i = 0;
	while (y < _listNbr.size())
	{
		_main.push_back(_listNbr[y]);
		y += lvl * 2;
		if (x > lvl - 1)
			_pend.push_back(std::make_pair(_listNbr[x], i));
		x += lvl * 2;
		++i;
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
template<typename T, typename Tpair>
void	PmergeMe<T, Tpair>::swapElement(size_t index1, size_t index2)
{
	size_t	x = index1;
	size_t	y = index2;

	while (x < y)
	{
		std::swap(_pend[x - 1].first, _pend[y - 2].first);
		x++;
		y--;
	}
}

template<typename T, typename Tpair>
void	PmergeMe<T, Tpair>::jacobsthal(void)
{
	size_t	index1 = 1;
	size_t	index2 = 1;
	size_t	index3;

	for (size_t i = 0; i < _pend.size(); ++i)
	{
		index3 = index1 * 2 + index2;
		if ((i + 2) == index3)
		{
			index1 = index2;
			index2 = index3;
			this->swapElement(index1, index2);
		}
	}
}

template<typename T, typename Tpair>
void	PmergeMe<T, Tpair>::insertIntoMain(size_t lvl)
{
	typename T::iterator	posMain;
	size_t					i = 0;
	size_t					count = 0;

	(void)lvl;
	this->jacobsthal();
	while (i < _pend.size())
	{
		//_main.begin() + _pend[i].second + 2 + count;
		//_main.begin() + i + 2 + count
		posMain = upper_bound(_main.begin(), _main.begin() + _pend[i].second + 2 + count, _pend[i].first); //i + 2 > posA of B
		this->insertElementsIntoList(lvl, *posMain, _pend[i].first);
		_main.insert(posMain, _pend[i].first); 
		++i;
		++count;
	}
	i = 0;
	while (i < _odd.size())
	{
		posMain = upper_bound(_main.begin(), _main.end(), _odd[i]);
		if (posMain == _main.end())
		{
			++i; // pose probleme ?  12 25 36 66 102
				 //placer à la fin ? 
			continue ;
		}
		this->insertElementsIntoList(lvl, *posMain, _odd[i]);
		_main.insert(posMain, _odd[i]); 
		++i;
	}
}

//Cherche la paire du pend dans la liste a partie de la valeur, trouve ensuite sa future position 
//par la position du nombre superieur a la valeur, et echange les places des paires.
template<typename T, typename Tpair>
void	PmergeMe<T, Tpair>::insertElementsIntoList(size_t lvl, int valueA, int valueB)
{
	size_t	posA = 0;
	size_t	posB;
	T		groupB(lvl);

	for (size_t i = 0; i < _listNbr.size(); ++i)
	{
		if (_listNbr[i] == valueB )//&& (i + 1) % lvl == 0)
			posB = i;
	}
	size_t	groupB_start = posB - (lvl - 1);
	for (size_t i = 0; i < lvl; ++i)
	{
		groupB[i] = _listNbr[groupB_start + i];
	}
	_listNbr.erase(_listNbr.begin() + groupB_start, _listNbr.begin() + groupB_start + lvl); //lvl 1 ? 

	for (size_t i = 0; i < _listNbr.size(); ++i)
	{
		if (_listNbr[i] == valueA)// && (i + 1) % lvl == 0)
		{
			posA = i;
			break; // si doublon prend le premier et break, pour éviter d'avoir celui d'apres
		}
	}
	size_t	groupA_start = posA - (lvl - 1);
	
	_listNbr.insert(_listNbr.begin() + groupA_start, groupB.begin(), groupB.end());
}

template<typename T, typename Tpair>
void PmergeMe<T, Tpair>::printList(void)
{
    for (size_t i = 0; i < _listNbr.size(); ++i)
    {
        std::cout << _listNbr[i] << " ";
    }
	std::cout << std::endl;
}

//ENLEVERRR
template<typename T, typename Tpair>
void PmergeMe<T, Tpair>::printMainPend(void)
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
        std::cout << _pend[i].first << " ";
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
template class PmergeMe<std::vector<int>, std::vector<std::pair<int, int> > >;
