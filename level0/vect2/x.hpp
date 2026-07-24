// 1715
#ifndef X_HPP
#define X_HPP

#include <iostream>
class vect2{
	private:
		int x,y;
	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2& o);
		~vect2();

		vect2& operator=(const vect2& o);
		int operator[](int n) const;
		int& operator[](int n) ;

		vect2& operator+=(const vect2& o);
		vect2 operator+(const vect2& o);
		vect2 operator-() const;
		vect2& operator-=(const vect2& o);
		vect2 operator-(const vect2& o);	
};

std::ostream& operator<<(std::ostream& os, const vect2& o);

#endif
