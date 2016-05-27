#include <iostream>
#include "fgroup.h"
#include "ecurve.h"

int main()
{
	EPoint::a = 0;
	EPoint::b = 3;
	FNumber::module = 7;
	EPoint a(3, 3);
	std::cout << 2 * a << std::endl;
	//int n, k;
	//EPoint p, q;
	//std::cout << "p = ";
	//std::cin >> FNumber::module;
	//std::cout << "a = ";
	//std::cin >> EPoint::a;
	//std::cout << "b = ";
	//std::cin >> EPoint::b;
	//std::cout << "n = ";
	//std::cin >> n;
	//std::cout << "k = ";
	//std::cin >> k;
	//std::cout << "P = ";
	//std::cin >> p;
	//std::cout << "Q = ";
	//std::cin >> q;

	//std::cout << std::endl;
	//EPoint np = n * p;
	//std::cout << "nP = " << np << std::endl;
	//EPoint kq = k * q;
	//std::cout << "kQ = " << kq << std::endl;
	//std::cout << "nP + kQ = " << n * p + k * q << std::endl;
	/*std::cout << 21 * EPoint(0, 30) << std::endl;*/


	/*FNumber::module = 5;
	EPoint::a = 1;
	EPoint::b = 1;
	EPoint p(2, 1);
	std::cout << 3 * p << std::endl;*/
	return 0;
}

