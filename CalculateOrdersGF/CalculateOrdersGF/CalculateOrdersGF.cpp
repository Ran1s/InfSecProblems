#include <iostream>
#include "fgroup.h"
#include <utility>
#include <map>


int calc_order(const FNumber& fnumber)
{
	int order = 1;
	FNumber cur_fnumber = fnumber;
	while (!(cur_fnumber == 1))
	{
		cur_fnumber *= fnumber;
		order++;
	}
	return order;
}

std::map<int, int> calc_distribution()
{
	std::map<int, int> distribution;
	for (int i = 1; i < FNumber::module; i++)
	{
		distribution[calc_order(i)]++;
	}
	return distribution;
}

int main()
{
	//std::cout << "p = ";
	//std::cin >> FNumber::module;
	FNumber::module = 19;
	auto distribution = calc_distribution();
	std::cout << "order: count" << std::endl;
	for (std::pair<int, int> item : distribution)
	{
		std::cout << item.first << ": " << item.second << std::endl;
	}
    return 0;
}

