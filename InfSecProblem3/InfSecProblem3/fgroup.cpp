#include "fgroup.h"

int FNumber::module = 7;
FNumber::FNumber() : val(0) {}
FNumber::FNumber(int val)
{
	val %= module;
	val += module;
	val %= module;
	this->val = val;
}
FNumber::FNumber(const FNumber& num) : val(num.val) {}
FNumber& FNumber::operator=(const FNumber& num)
{
	val = num.val;
	return *this;
}
FNumber operator+(const FNumber& lhs, const FNumber& rhs)
{
	return (lhs.val + rhs.val);
}
FNumber operator*(const FNumber& lhs, const FNumber& rhs)
{
	return (lhs.val * rhs.val);
}
FNumber operator-(const FNumber& lhs, const FNumber& rhs)
{
	return lhs + rhs * -1;
}
FNumber& FNumber::operator*=(const FNumber& rhs)
{
	//безопасна€ верси€
	*this = *this * rhs;

	//оптимизированна€ верси€
	//val *= rhs.val;
	//val %= module;
	//val += module;
	//val %= module;
	return *this;
}
FNumber& FNumber::operator+=(const FNumber& rhs)
{
	*this = *this + rhs;
	return *this;
}
FNumber& FNumber::operator-=(const FNumber& rhs)
{
	*this += rhs * -1;
	return *this;
}
FNumber FNumber::pow(FNumber num, int p)
{
	if (p >= 0)
	{
		FNumber res(1);
		while (p > 0)
		{
			if (p % 2 == 0)
			{
				p /= 2;
				num *= num;
			}
			else
			{
				res *= num;
				p--;
			}
		}
		return res;
	}
	else
	{
		return pow(inverse(num), -p);
	}
}

FNumber FNumber::inverse(const FNumber& num)
{
	// возможно, стоит переделать через функцию Ёйлера
	return FNumber::pow(num, FNumber::module - 2);
}
FNumber operator/(const FNumber&lhs, const FNumber& rhs)
{
	return lhs * FNumber::inverse(rhs);
}
FNumber& FNumber::operator/=(const FNumber& rhs)
{
	return (*this) / rhs;
}
int FNumber::get_value() const
{
	return val;
}
bool operator<(const FNumber& lhs, const FNumber& rhs)
{
	return lhs.val < rhs.val;
}
bool operator==(const FNumber& lhs, const FNumber& rhs)
{
	return lhs.val == rhs.val;
}
std::ostream& operator<<(std::ostream& out, const FNumber& num)
{
	out << num.val;
	return out;
}
std::istream& operator >> (std::istream& in, FNumber& num)
{
	in >> num.val;
	return in;
}