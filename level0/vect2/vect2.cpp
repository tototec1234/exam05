#include "vect2.hpp"
// 1　Constructors / Destructor
vect2::vect2() : x(0), y(0) {}
vect2::vect2(int x, int y) : x(x), y(y) {}
vect2::vect2(const vect2& src) : x(src.x), y(src.y) {}
vect2::~vect2() {}

// 1　Assignment
vect2& vect2::operator=(const vect2& src){
	x = src.x;
	y = src.y;
	return *this;}

// 2　Index
int  vect2::operator[](int i) const { return i == 0 ? x : y; }
int& vect2::operator[](int i)       { return i == 0 ? x : y; }

// 3　Unary minus
vect2 vect2::operator-() const { return vect2(-x, -y); }

// 4　Compound assignment (the "core" operations)
vect2& vect2::operator+=(const vect2& o) { x += o.x; y += o.y; return *this; }
vect2& vect2::operator-=(const vect2& o) { x -= o.x; y -= o.y; return *this; }

vect2& vect2::operator*=(int n)          { x *= n;   y *= n;   return *this; }

// 5　Binary operators — copy then apply compound
vect2 vect2::operator+(const vect2& o) const { return vect2(*this) += o; }
vect2 vect2::operator-(const vect2& o) const { return vect2(*this) -= o; }
vect2 vect2::operator*(int n)          const { return vect2(*this) *= n; }

// 6　Pre-increment / pre-decrement
vect2& vect2::operator++() { ++x; ++y; return *this; }
vect2& vect2::operator--() { --x; --y; return *this; }

// 6　Post-increment / post-decrement — save, apply pre, return saved
vect2 vect2::operator++(int) { vect2 tmp(*this); ++(*this); return tmp; }
vect2 vect2::operator--(int) { vect2 tmp(*this); --(*this); return tmp; }

// 7　Comparison
bool vect2::operator==(const vect2& o) const { return x == o.x && y == o.y; }
bool vect2::operator!=(const vect2& o) const { return !(*this == o); }

// 8　Free functions
vect2 operator*(int n, const vect2& o) { return o * n; }

// 9　MUST memorize (subject output)
std::ostream& operator<<(std::ostream& os, const vect2& o){
	return os << "{" << o[0] << ", " << o[1] << "}";
}
