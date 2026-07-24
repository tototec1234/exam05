#include "x.hpp"
#include <iostream>

vect2::vect2() : x(0), y(0){}
vect2::vect2(int num1, int num2) : x(num1), y(num2){}
vect2::vect2(const vect2& o) : x(o.x), y(o.y){}
vect2::~vect2(){};

vect2& vect2::operator=(const vect2& o){
	x = o.x;
	y = o.y;
	return *this;}

	int vect2::operator[](int n) const { return n == 0 ? x : y;}
	int& vect2::operator[](int n) { return n == 0 ? x : y;}


vect2& vect2::operator+=(const vect2& o){
	this->x += o.x;
	this->y += o.y;
	return *this;
}

vect2 vect2::operator+(const vect2& o){
	return *this += o;
}

vect2 vect2::operator-() const { return vect2(-x, -y); }


vect2& vect2::operator-=(const vect2& o){
	x -= o.x;
	y -= o.y;
	return *this;
	// return *this += -o;
}

vect2 vect2::operator-(const vect2& o){
	return *this -= o; 
}

std::ostream& operator<<(std::ostream& os, const vect2& o){
	return os << "{" << o[0] << ", " << o[1] << "}" ;
}