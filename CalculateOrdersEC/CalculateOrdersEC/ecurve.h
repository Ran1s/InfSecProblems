#pragma once
#include "fgroup.h"

class EPoint
{
public:
	static int a;
	static int b;

	FNumber x;
	FNumber y;

	EPoint();
	EPoint(FNumber, FNumber);
	EPoint(const EPoint&);
	EPoint& operator=(const EPoint&);
	friend bool operator==(const EPoint&, const EPoint&);
	friend EPoint operator+(const EPoint&, const EPoint&);
	static EPoint inverse(const EPoint&);
	friend EPoint operator-(const EPoint&, const EPoint&);
	EPoint& operator+=(const EPoint&);
	EPoint& operator-=(const EPoint&);
	friend EPoint operator*(int, EPoint);
	friend EPoint operator*(EPoint, int);
	friend std::ostream& operator<<(std::ostream&, const EPoint&);
	friend std::istream& operator >> (std::istream&, EPoint&);
};