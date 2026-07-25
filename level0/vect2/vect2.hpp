#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
private:
	int x;
	int y;
public:
	vect2();
	vect2(int x, int y);
	vect2(const vect2& src);
	~vect2();
	vect2& operator=(const vect2& src);

	int  operator[](int i) const;
	int& operator[](int i);

	vect2  operator-() const;

	vect2& operator+=(const vect2& o);
	vect2& operator-=(const vect2& o);
	// vect2& operator*=(const vect2& o);	// optional
	vect2& operator*=(int n);

	vect2 operator+(const vect2& o) const;
	vect2 operator-(const vect2& o) const;
	// vect2 operator*(const vect2& o) const;	// optional
	vect2 operator*(int n) const;

	vect2& operator++();
	vect2& operator--();
	vect2  operator++(int);
	vect2  operator--(int);

	bool operator==(const vect2& o) const;
	bool operator!=(const vect2& o) const;
};

vect2 operator*(int n, const vect2& o);
std::ostream& operator<<(std::ostream& os, const vect2& o);

#endif
