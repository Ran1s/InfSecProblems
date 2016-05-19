#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <utility>
#include "fgroup.h"


bool shanks_method(const FNumber& g, const FNumber& y, FNumber& x)
{
	int m = static_cast<int>(sqrt(FNumber::module)) + 1;
	std::map<FNumber, int> big_steps;
	FNumber t = FNumber::pow(g, m);
	FNumber cur_t = t;
	for (int u = 1; u <= m; u++)
	{
		if (big_steps.find(cur_t) == big_steps.end())
		{
			big_steps.insert(std::make_pair(cur_t, u));
		}
		cur_t *= t;
	}
	FNumber cur = y;
	for (int v = 0; v <= m; v++)
	{
		auto it = big_steps.find(cur);
		if (it != big_steps.end())
		{
			x  = it->second * m - v;
			return true;
		}
		cur *= g;
	}
	return false;
}

int main()
{
	FNumber g;
	FNumber y;
	FNumber x;
	std::cout << "g = ";
	std::cin >> g;
	std::cout << "y = ";
	std::cin >> y;
	std::cout << "p = ";
	std::cin >> FNumber::module;

	if (shanks_method(g, y, x))
	{
		std::cout << "x = " << x << std::endl << std::endl;

		for (int i = 0; i < 4; i++)
		{
			FNumber a, b;
			std::cout << "A = ";
			std::cin >> a;
			std::cout << "B = ";
			std::cin >> b;
			std::cout << "M = " << FNumber::pow(a, -x.get_value()) * b << std::endl << std::endl;
		}

	}
	else
	{
		std::cout << "error" << std::endl;
	}


	return 0;
}
