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
		Vector2f operator*(float factor) const;
		Vector2f operator/(const Vector2f& other) const;
		Vector2f operator/(float factor) const;
		Vector2f operator-(const Vector2f& other) const;
		Vector2f operator-() const;

		// Methods
		float dot(const Vector2f& other) const; // scalar product
		float isOrthogonal(const Vector2f& other) const;
		float norm() const;
		
		Vector2f normalize() const;

		static Vector2f absolute(const Vector2f& other);
	};

	struct Vector3f {
	private :
		Vector3f() = delete;

	public :
		float x;
		float y;
		float z;

		// Constructor
		Vector3f(float x, float y, float z);

		// Operators overloading
		Vector3f operator+(const Vector3f& other) const;
		Vector3f operator+(const Vector2f& other) const;
		Vector3f operator*(const Vector3f& other) const;
		Vector3f operator*(float factor) const;
		Vector3f operator/(const Vector3f& other) const;
		Vector3f operator/(float factor) const;
		Vector3f operator-(const Vector3f& other) const; 
		Vector3f operator-() const;

		// Scalar product
		float dot(const Vector3f& other) const;
		// Vectorial product
		Vector3f vectorial(const Vector3f& other) const;
		// True if the current vector is orthogonal to the other
		float isOrthogonal(const Vector3f& other) const;
		// Norm of the vector
		float norm() const;

		// Returns a new vector corresponding to the current one, normalized
		Vector3f normalize() const;

		// Returns a new vector. Its coordinates are the absolute of the ones of the vector passed in parameter
		static Vector3f absolute(const Vector3f& other);
	};
}