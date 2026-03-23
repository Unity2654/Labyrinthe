#include "Vector.h"
#include <cmath>

namespace gloop {
	gloop::Vector3f::Vector3f(float x, float y, float z):
		x(x),
		y(y),
		z(z){}

	Vector3f Vector3f::operator+(const Vector3f& other) const{
		return Vector3f{x + other.x, y+other.y, z + other.z};
	}

	Vector3f Vector3f::operator+(const Vector2f& other) const{
		return Vector3f{x + other.x, y + other.y, z};
	}

	Vector3f Vector3f::operator*(const Vector3f& other) const{
		return Vector3f{ x * other.x, y * other.y, z * other.z };
	}

	Vector3f Vector3f::operator*(float factor) const{
		return Vector3f{ x * factor, y * factor, z * factor };
	}

	Vector3f Vector3f::operator/(const Vector3f& other) const{
		return Vector3f{ x / other.x, y / other.y, z / other.z };
	}

	Vector3f Vector3f::operator/(float factor) const{
		return Vector3f{ x / factor, y / factor, z / factor };
	}

	Vector3f Vector3f::operator-(const Vector3f& other) const{
		return Vector3f{ x - other.x, y - other.y, z - other.z };
	}

	float Vector3f::dot(const Vector3f& other) const{
		return x * other.x + y * other.y + z * other.z;
	}

	Vector3f Vector3f::vectorial(const Vector3f& other) const
	{
		return Vector3f{
			y * other.z - z * other.y,
			x * other.z - z * other.x,
			x * other.y - y * other.x
		};
	}

	float Vector3f::isOrthogonal(const Vector3f& other) const{
		return this->dot(other) == 0;
	}

	float Vector3f::norm() const{
		return sqrt(x*x + y*y + z*z);
	}

	Vector3f Vector3f::absolute(const Vector3f& other){
		return Vector3f(abs(other.x), abs(other.y), abs(other.z));
	}

	Vector2f::Vector2f(float x, float y): x(x), y(y){}

	Vector2f Vector2f::operator+(const Vector2f& other) const {
		return Vector2f{ x + other.x, y + other.y };
	}

	Vector2f Vector2f::operator*(const Vector2f& other) const {
		return Vector2f{ x * other.x, y * other.y };
	}

	Vector2f Vector2f::operator*(float factor) const{
		return Vector2f{ x * factor, y * factor};
	}

	Vector2f Vector2f::operator/(const Vector2f& other) const {
		return Vector2f{ x / other.x, y / other.y };
	}

	Vector2f Vector2f::operator/(float factor) const{
		return Vector2f{ x / factor, y / factor };
	}

	Vector2f Vector2f::operator-(const Vector2f& other) const {
		return Vector2f{ x - other.x, y - other.y};
	}

	float Vector2f::dot(const Vector2f& other) const {
		return x * other.x + y * other.y;
	}

	float Vector2f::isOrthogonal(const Vector2f& other) const {
		return this->dot(other) == 0;
	}

	float Vector2f::norm() const{
		return sqrt(x * x + y * y);
	}

	Vector2f Vector2f::absolute(const Vector2f& other){
		return Vector2f(abs(other.x), abs(other.y));
	}

}