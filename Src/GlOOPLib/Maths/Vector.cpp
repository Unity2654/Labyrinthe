#include "Vector.h"

namespace gloop {
	gloop::Vector3f::Vector3f(float x, float y, float z):
		x(x),
		y(y),
		z(z){}

	Vector3f Vector3f::operator+(const Vector3f& other) const{
		return Vector3f{x + other.x, y+other.y, z + other.z};
	}

	Vector3f Vector3f::operator*(const Vector3f& other) const{
		return Vector3f{ x * other.x, y * other.y, z * other.z };
	}

	Vector3f Vector3f::operator/(const Vector3f& other) const{
		return Vector3f{ x / other.x, y / other.y, z / other.z };
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

	Vector2f::Vector2f(float x, float y): x(x), y(y){}

	Vector2f Vector2f::operator+(const Vector2f& other) const {
		return Vector2f{ x + other.x, y + other.y };
	}

	Vector2f Vector2f::operator*(const Vector2f& other) const {
		return Vector2f{ x * other.x, y * other.y };
	}

	Vector2f Vector2f::operator/(const Vector2f& other) const {
		return Vector2f{ x / other.x, y / other.y };
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
}