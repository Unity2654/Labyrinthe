#pragma once

namespace gloop {
	struct Vector3f {
	private :
		Vector3f();

	public :
		float x;
		float y;
		float z;

		// Constructor
		Vector3f(float x, float y, float z);

		// Operators overloading
		Vector3f operator+(const Vector3f& other) const;
		Vector3f operator*(const Vector3f& other) const;
		Vector3f operator/(const Vector3f& other) const;
		Vector3f operator-(const Vector3f& other) const; 

		// Methods
		float dot(const Vector3f& other) const; // scalar product
		Vector3f vectorial(const Vector3f& other) const; // vectorial product
		float isOrthogonal(const Vector3f& other) const;

	};
}