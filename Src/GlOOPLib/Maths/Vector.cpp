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

	float* Vector3f::asArray() const
	{
		float res[] = { x, y, z };
		return res;
	}

}