#include <iostream>
#include "fgroup.h"
#include "ecurve.h"
#include <map>

int calc_order(const EPoint& epoint)
{
	using namespace std::rel_ops;
	int order = 1;
	EPoint cur_epoint = epoint;
	while (cur_epoint != EPoint(0, 0))
	{
		cur_epoint += epoint;
		order++;
	}
	return order;
}

std::map<int, int> calc_distribution()
{
	std::map<int, int> distribution;
	for (int i = 0; i < FNumber::module; i++)
	{
		for (int j = 0; j < FNumber::module; j++)
		{
			FNumber x(i), y(j);
			if (FNumber::pow(y, 2) == FNumber::pow(x, 3) + FNumber(EPoint::a) * x + FNumber(EPoint::b))
			{
				distribution[calc_order(EPoint(x, y))]++;
			}
		}
	}
	return distribution;
}

int main()
{
	FNumber::module = 31;
	EPoint::a = 15;
	EPoint::b = 1;

	auto distribution = calc_distribution();
	std::cout << "order: count" << std::endl;
	for (std::pair<int, int> item : distribution)
	{
		std::cout << item.first << ": " << item.second << std::endl;
	}
	return 0;
}

