#include <iostream>
#include <utility>
class FNumber 
{
public:
	static int module;
	FNumber();
	FNumber(int val);
	FNumber(const FNumber&);
	FNumber& operator=(const FNumber&);

	friend FNumber operator+(const FNumber&, const FNumber&);
	friend FNumber operator*(const FNumber&, const FNumber&);
	friend FNumber operator-(const FNumber&, const FNumber&);
	friend FNumber operator/(const FNumber&, const FNumber&);
	friend bool operator==(const FNumber&, const FNumber&);
	friend bool operator<(const FNumber&, const FNumber&);

	FNumber& operator*=(const FNumber&);
	FNumber& operator+=(const FNumber&);
	FNumber& operator-=(const FNumber&);
	FNumber& operator/=(const FNumber&);
	FNumber& operator++();
	FNumber operator++(int);
	FNumber& operator--();
	FNumber operator--(int);

	static FNumber pow(FNumber, int);
	static FNumber inverse(const FNumber&);

	int get_value() const;

	friend std::ostream& operator<<(std::ostream&, const FNumber&);
	friend std::istream& operator >> (std::istream&, FNumber&);
private:
	int val;
};