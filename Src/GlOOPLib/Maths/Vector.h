#pragma once


// Note: If we need more that 2D and 3D coordinates, add a generic vector class using templates instead of this ****** implementation.
namespace gloop {
	struct Vector2f {
		Vector2f() = delete;
	public :
		float x;
		float y;

		// Constructor
		Vector2f(float x, float y);

		// Operators overloading
		Vector2f operator+(const Vector2f& other) const;
		Vector2f operator*(const Vector2f& other) const;
		Vector2f operator/(const Vector2f& other) const;
		Vector2f operator-(const Vector2f& other) const;

		// Methods
		float dot(const Vector2f& other) const; // scalar product
		float isOrthogonal(const Vector2f& other) const;

	};

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