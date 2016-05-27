#include <iostream>
#include "ecurve.h"
int EPoint::a = 1;
int EPoint::b = 1;

EPoint::EPoint() : x(0), y(0) {}
EPoint::EPoint(FNumber x, FNumber y)
{
	this->x = x;
	this->y = y;
}
EPoint::EPoint(const EPoint& p)
{
	this->x = p.x;
	this->y = p.y;
}
EPoint& EPoint::operator=(const EPoint& p)
{
	x = p.x;
	y = p.y;
	return *this;
}
bool operator==(const EPoint& lhs, const EPoint& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
EPoint operator+(const EPoint& lhs, const EPoint& rhs)
{
	using namespace std::rel_ops;
	if (lhs == EPoint(0, 0))
	{
		return rhs;
	}
	if (rhs == EPoint(0, 0))
	{
		return lhs;
	}
	FNumber lambda;
	if (lhs == rhs)
	{
		if (2 * lhs.y == 0)
		{
			return EPoint(0, 0);
		}
		lambda = (3 * FNumber::pow(lhs.x, 2) + EPoint::a) / (2 * lhs.y);
	}
	else
	{
		if (rhs.x == lhs.x && rhs.y != lhs.y)
		{
			return EPoint(0, 0);
		}
		lambda = (rhs.y - lhs.y) / (rhs.x - lhs.x);
	}
	FNumber x = FNumber::pow(lambda, 2) - lhs.x - rhs.x;
	FNumber y = lambda * (lhs.x - x) - lhs.y;
	return EPoint(x, y);
}
EPoint EPoint::inverse(const EPoint& p)
{
	return EPoint(p.x, p.y * -1);
}
EPoint operator-(const EPoint& lhs, const EPoint& rhs)
{
	return lhs + EPoint::inverse(rhs);
}
EPoint& EPoint::operator+=(const EPoint& rhs)
{
	*this = *this + rhs;
	return *this;
}
EPoint& EPoint::operator-=(const EPoint& rhs)
{
	*this = *this + inverse(rhs);
	return *this;
}
EPoint operator*(int k, EPoint p)
{
	if (k < 1)
		throw std::invalid_argument("k can't be negative");
	EPoint ans(0, 0);
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
EPoint operator*(EPoint p, int k)
{
	return k * p;
}
std::ostream& operator<<(std::ostream& out, const EPoint& p)
{
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}
std::istream& operator >> (std::istream& in, EPoint& p)
{
	in >> p.x >> p.y;
	return in;
}
