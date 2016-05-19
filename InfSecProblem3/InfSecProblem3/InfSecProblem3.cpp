#include <iostream>
#include "fgroup.h"

class EPoint
{
public:
	static int a;
	static int b;

	FNumber x;
	FNumber y;

	EPoint() : x(0), y(0) {}
	EPoint(FNumber x, FNumber y)
	{
		this->x = x;
		this->y = y;
	}
	EPoint(const EPoint& p)
	{
		this->x = p.x;
		this->y = p.y;
	}
	EPoint& operator=(const EPoint& p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
	friend bool operator==(const EPoint& lhs, const EPoint& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
	friend EPoint operator+(const EPoint& lhs, const EPoint& rhs)
	{
		if (lhs == EPoint(0, 0) || rhs == EPoint(0, 0))
		{
			return EPoint(0, 0);
		}
		FNumber lambda;
		if (lhs == rhs)
		{
			if (2 * lhs.y == 0)
			{
				return EPoint(0, 0);
			}
			lambda = (3 * FNumber::pow(lhs.x, 2) + a) / (2 * lhs.y);
		}
		else
		{
			if (rhs.x == lhs.x)
			{
				return EPoint(0, 0);
			}
			lambda = (rhs.y - lhs.y) / (rhs.x - lhs.x);
		}
		FNumber x = FNumber::pow(lambda, 2) - lhs.x - rhs.x;
		FNumber y = lambda * (lhs.x - x) - lhs.y;
		return EPoint(x, y);
	}
	static EPoint inverse(const EPoint& p)
	{
		return EPoint(p.x, p.y * -1);
	}
	friend EPoint operator-(const EPoint& lhs, const EPoint& rhs)
	{
		return lhs + inverse(rhs);
	}
	EPoint& operator+=(const EPoint& rhs)
	{
		*this = *this + rhs;
		return *this;
	}
	EPoint& operator-=(const EPoint& rhs)
	{
		*this = *this + inverse(rhs);
		return *this;
	}
	friend EPoint operator*(int k, EPoint p)
	{
		if (k < 1)
			throw std::invalid_argument("k can't be negative");
		EPoint ans = p;
		k--;
		while (k > 0)
		{
			if (k % 2 == 0)
			{
				k /= 2;
				p += p;
			}
			else
			{
				ans += p;
				k--;
			}
		}
		return ans;
	}
	friend const EPoint operator*(EPoint p, int k)
	{
		return k * p;
	}
	friend std::ostream& operator<<(std::ostream& out, const EPoint& p)
	{
		out << "(" << p.x << ", " << p.y << ")";
		return out;
	}
	friend std::istream& operator>>(std::istream& in, EPoint& p)
	{
		in >> p.x >> p.y;
		return in;
	}
};
int EPoint::a = 1;
int EPoint::b = 1;
int main()
{
	/*EPoint::a = 15;
	EPoint::b = 1;
	FNumber::module = 31;*/
	int n, k;
	EPoint p, q;
	std::cout << "p = ";
	std::cin >> FNumber::module;
	std::cout << "a = ";
	std::cin >> EPoint::a;
	std::cout << "b = ";
	std::cin >> EPoint::b;
	std::cout << "n = ";
	std::cin >> n;
	std::cout << "k = ";
	std::cin >> k;
	std::cout << "P = ";
	std::cin >> p;
	std::cout << "Q = ";
	std::cin >> q;

	std::cout << std::endl;
	EPoint np = n * p;
	EPoint kq = k * q;
	std::cout << "nP + kQ = " << n * p + k * q << std::endl;
	/*std::cout << 21 * EPoint(0, 30) << std::endl;*/


	/*FNumber::module = 5;
	EPoint::a = 1;
	EPoint::b = 1;
	EPoint p(2, 1);
	std::cout << 3 * p << std::endl;*/
	return 0;
}

