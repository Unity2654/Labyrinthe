#pragma once
#include <vector>
#include "../Maths/Vector.h"


namespace gloop {

	// A rectangle, destined to be used to store the data of a hitbox for collisions  
	struct Rectangle {
	public:
		const Vector3f position;
		const double width;
		const double height;

		// Constructors
		Rectangle() = delete;
		/**
	     * Constructs a rectangle from its up left corner, and its width/height 
		 */
		Rectangle(Vector3f position, double width, double height);
		
		static Rectangle fromCenter(Vector3f center, double width, double height);
		/**
		 * Construct a rectangle from its up right and down left corners
		 */
		static Rectangle fromUrDlCorners(Vector3f upRightCorner, Vector3f downLeftCorner);
		/**
		 * Construct a rectangle from its up left and down right corners
		 */
		static Rectangle fromUlDrCorners(Vector3f upLeftCorner, Vector3f downRightCorner);

		Vector3f getCenter() const;

		/**
		 * Gets a vector containing the four corners of the square in the following order : { UL, UR, DL, DR }
		*/
		std::vector<Vector3f> getCorners() const;
	};

	class Collidable {
	public :
		double getMass(){}

		Rectangle getCollisionBox(){}
	};

}