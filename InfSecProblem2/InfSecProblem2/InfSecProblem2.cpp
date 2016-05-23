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
	static std::vector<FNumber> irreducible_polynom;
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
		for (int i = 1; i <= number && !gen_found; i++)
		{
			std::vector<FNumber> gen = from_decimal(i, number);
			gen_found = check_generator(gen, alpha);
		}
	}
	static std::vector<FNumber> from_decimal(int n, const int& scale_notation)
	{
		std::vector<FNumber> ans;
		while (n > 0)
		{
			ans.push_back(n % scale_notation);
			n /= scale_notation;
		}
		return ans;
	}
	// если alpha^(number^degree) == 1, то это генератор, иначе нет
	static bool check_generator(const std::vector<FNumber>& gen, std::vector<std::vector<FNumber>>& alpha)
	{
		int count_elements = std::pow(number, degree);
		alpha.resize(count_elements);
		alpha[0] = { 1 };
		for (int deg = 1; deg < count_elements; deg++)
		{
			alpha[deg] = mult(alpha[deg - 1], gen);
			simplify(alpha[deg]);
			if (one(alpha[deg]) && deg != count_elements - 1)
			{
				alpha.clear();
				return false;
			}
		}
		return true;
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
	static std::vector<FNumber> subtr(const std::vector<FNumber>& lhs, const std::vector<FNumber>& rhs)
	{
		std::vector<FNumber> ans(std::max(lhs.size(), rhs.size()));
		for (size_t i = 0; i < ans.size(); i++)
		{
			if (i < lhs.size() && i < rhs.size())
			{
				ans[i] = lhs[i] - rhs[i];
			}
			else if (i < lhs.size())
			{
				ans[i] = lhs[i];
			}
			else
			{
				ans[i] = 0 - rhs[i];
			}
		}
		delete_lead_zeros(ans);
		return ans;
	}
	static void simplify(std::vector<FNumber>& polynom)
	{
		while (polynom.size() >= irreducible_polynom.size())
		{
			FNumber divider = polynom[polynom.size() - 1] / irreducible_polynom[irreducible_polynom.size() - 1];
			std::vector<FNumber> minus = irreducible_polynom;
			for (size_t i = 0; i < minus.size(); i++)
			{
				minus[i] *= divider;
			}
			polynom = subtr(polynom, minus);
			delete_lead_zeros(polynom);
		}
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
		return pol.size() == 1 && pol[0] == 1;
	}

	std::vector<FNumber> polynom;
};
int FPolynom::degree = 1;
int FPolynom::number = 1;
std::vector<FNumber> FPolynom::irreducible_polynom = { 1 };
bool FPolynom::calculated = false;

int main()
{
	std::cout << "module, degree: ";
	std::cin >> FPolynom::number >> FPolynom::degree;
	FNumber::module = FPolynom::number;

	std::cout << "irreducible polynom: ";
	std::string toch;
	std::cin >> toch;

	//костыль для удобного ввода
	std::vector<FNumber> tochv(toch.size());
	for (size_t i = 0; i < toch.size(); i++)
	{
		tochv[i] = toch[i] - '0';
	}
	//FPolynom::to_change = tochv;
	FPolynom::irreducible_polynom = tochv;

	FPolynom a, b, c, d;
	std::cout << "first problem: first polynom, second polynom: ";
	std::cin >> a >> b;
	std::cout << "sum: " << a + b << std::endl;
	std::cout << "mult: " << a * b << std::endl;
	std::cout << "second problem: polynom, degree: ";
	int p;
	std::cin >> c >> p;
	std::cout << FPolynom::pow(c, p) << std::endl;
	std::cout << "third problem: polynom: ";
	std::cin >> d;
	std::cout << "inverse polynom: " << FPolynom::inverse(d) << std::endl;
    return 0;
}

