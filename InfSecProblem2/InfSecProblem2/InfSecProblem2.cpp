#include <iostream>
#include "fgroup.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
std::vector<std::vector<FNumber>> alpha;
class FPolynom
{
public:
	static int number;
	static int degree;
	static FNumber what_change;
	static std::vector<FNumber> to_change;
	static bool calculated;
	

	FPolynom() : polynom() {}
	
	FPolynom(std::vector<FNumber> polynom)
	{
		this->polynom = polynom;
		simplify(this->polynom);
		if (!calculated)
		{
			calculate(alpha);
		}
	}

	friend FPolynom operator+(const FPolynom& lhs, const FPolynom& rhs)
	{
		return add(lhs.polynom, rhs.polynom);
	}
	friend FPolynom operator*(const FPolynom& lhs, const FPolynom& rhs)
	{
		int pos = find(lhs) + find(rhs);
		pos %= static_cast<int>(std::pow(number, degree)) - 1;
		return alpha[pos];
	}
	static FPolynom pow(const FPolynom& polynom, int pow)
	{
		int pos = (find(polynom)) * pow;
		pos %= static_cast<int>(std::pow(number, degree)) - 1;
		return alpha[pos];
	}
	friend bool operator==(const FPolynom& lhs, const FPolynom& rhs)
	{
		return lhs.polynom == rhs.polynom;
	}
	friend std::ostream& operator<<(std::ostream& out, const FPolynom& polynom)
	{
		for (size_t i = 0; i < polynom.polynom.size(); i++)
		{
			out << polynom.polynom[i];
		}
		for (size_t i = 0; i < degree - polynom.polynom.size(); i++)
		{
			out << 0;
		}
		return out;
	}
	friend std::istream& operator>>(std::istream& in, FPolynom& polynom)
	{
		std::vector<FNumber> elements;
		std::string str;
		in >> str;
		elements.resize(str.size());
		for (size_t i = 0; i < str.size(); i++)
		{
			elements[i] = str[i] - '0';
		}
		polynom = FPolynom(elements);
		return in;
	}
	static FPolynom inverse(const FPolynom& polynom)
	{
		int pos = static_cast<int>(std::pow(number, degree)) - 1;
		pos -= find(polynom);
		return alpha[pos];
	}
private:
	static int find(const FPolynom& polynom)
	{
		for (size_t i = 0; i < alpha.size(); i++)
		{
			if (alpha[i] == polynom)
				return i;
		}
		return -1;
	}

	static void calculate(std::vector<std::vector<FNumber>>& alpha)
	{
		bool gen_found = false;

		//по-моему это абсолютно не правильно, то есть работает только для полей 2^x, вроде
		//просто пробегаемся по всем возможным генераторам, проверяя его
		for (int num = 0; num < number && !gen_found; num++)
		{
			for (int numt = 0; numt < number && !gen_found; numt++)
			{
				std::vector<FNumber> gen = { num, numt };
				if (check_generator(gen, alpha))
				{
					gen_found = true;
					break;
				}
			}
		}
	}
	// если alpha^(number^degree) == 1, то это генератор, иначе нет
	static bool check_generator(const std::vector<FNumber>& gen, std::vector<std::vector<FNumber>>& alpha)
	{
		int count_elements = std::pow(number, degree);
		alpha.resize(count_elements);
		//std::vector<FNumber> cur = gen;
		alpha[0] = { 1 };
		for (int deg = 1; deg < count_elements; deg++)
		{
			alpha[deg] = mult(alpha[deg - 1], gen);
			simplify(alpha[deg]);
		}
		if (one(alpha[count_elements - 1]))
		{
			return true;
		}
		else
		{
			alpha.clear();
			return false;
		}
	}
	static std::vector<FNumber> mult(const std::vector<FNumber>& lhs, const std::vector<FNumber>& rhs)
	{
		std::vector<FNumber> ans(std::max(lhs.size(), rhs.size()) * 2);
		for (size_t i = 0; i < lhs.size(); i++)
		{
			for (size_t j = 0; j < rhs.size(); j++)
			{
				int degree = i + j;
				ans[degree] += lhs[i] * rhs[j];
			}
		}
		delete_lead_zeros(ans);
		simplify(ans);
		return ans;
	}
	static std::vector<FNumber> add(const std::vector<FNumber>& lhs, const std::vector<FNumber>& rhs)
	{
		std::vector<FNumber> ans(std::max(lhs.size(), rhs.size()));
		for (size_t i = 0; i < ans.size(); i++)
		{
			if (i < lhs.size() && i < rhs.size())
			{
				ans[i] = lhs[i] + rhs[i];
			}
			else if (i < lhs.size())
			{
				ans[i] = lhs[i];
			}
			else
			{
				ans[i] = rhs[i];
			}
		}
		delete_lead_zeros(ans);
		return ans;
	}
	static void simplify(std::vector<FNumber>& polynom)
	{
		for (int i = polynom.size() - 1; i >= degree; i--)
		{
			if (!(polynom[i] == 0))
			{
				std::vector<FNumber> temp(i - degree + 1);
				temp[i - degree] = polynom[i];
				temp = mult(temp, to_change);
				polynom = add(temp, polynom);
				polynom[i] -= what_change;
			}
		}
		delete_lead_zeros(polynom);
	}
	static void delete_lead_zeros(std::vector<FNumber>& polynom)
	{
		int i = polynom.size() - 1;
		for (; i >= 0; i--)
		{
			if (!(polynom[i] == 0))
			{
				break;
			}
		}
		polynom.resize(i + 1);
	}
	static bool one(const std::vector<FNumber>& pol)
	{
		if (pol.size() == 1)
		{
			if (pol[0] == 1)
			{
				return true;
			}
		}
		return false;
	}
	
	std::vector<FNumber> polynom;
};
int FPolynom::degree = 1;
int FPolynom::number = 1;
FNumber FPolynom::what_change = 1;
std::vector<FNumber> FPolynom::to_change = { 1 };
bool FPolynom::calculated = false;

int main()
{
	std::cout << "module, degree ";
	std::cin >> FPolynom::number >> FPolynom::degree;
	FNumber::module = FPolynom::number;

	std::cout << "what change, to change ";
	std::string toch;
	std::cin >> FPolynom::what_change >> toch;

	//костыль для удобного ввода
	std::vector<FNumber> tochv(toch.size());
	for (size_t i = 0; i < toch.size(); i++)
	{
		tochv[i] = toch[i] - '0';
	}
	FPolynom::to_change = tochv;

	FPolynom a, b, c, d;
	std::cout << "first problem: first polynom, second polynom ";
	std::cin >> a >> b;
	std::cout << "sum: " << a + b << std::endl;
	std::cout << "mult: " << a * b << std::endl;
	std::cout << "second problem: polynom, degree ";
	int p;
	std::cin >> c >> p;
	std::cout << FPolynom::pow(c, p) << std::endl;
	std::cout << "third problem: polynom ";
	std::cin >> d;
	std::cout << "inverse polynom: " << FPolynom::inverse(d) << std::endl;
    return 0;
}

