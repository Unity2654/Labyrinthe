#pragma once
#include "Cameraman.h"
#include "../Maths/Vector.h"

namespace gloop {
	
	// Base class for cameras
	// Preferably use overloaded classes
	class Camera {
	protected :
		Cameraman const& manager;
		Vector3f position{ 0.0,0.0,0.0 };
		bool active = false;

	public:
		Camera() = delete;
		Camera(Cameraman& manager);
		Camera(Cameraman& manager, Vector3f position);

		void setPosition(Vector3f position);
		Vector3f getPosition() const;

		// Projection part of the camera (glFrustum, gluPerspective or glOtrho, the rest should be handled by the manager)
		virtual void renderProjection() const;

		void activate();
		bool isActive() const;
	};

	// A camera using a view in perspective
	class PerspectiveCamera : public Camera {
	public :
		double foc; 
		double ratio;
		double cmin;
		double cmax;

		PerspectiveCamera() = delete;
		PerspectiveCamera(Cameraman& manager, double foc, double ratio, double cmin, double cmax);
		PerspectiveCamera(Cameraman& manager, Vector3f position ,double foc, double ratio, double cmin, double cmax);

		void renderProjection() const override;
	};

	// A camera using an orthogonal view
	class OrthogonalCamera : public Camera {
	public :
		double g;
		double d;
		double b;
		double h;
		double cmin;
		double cmax;

		OrthogonalCamera() = delete;
		OrthogonalCamera(Cameraman& manager, double g, double d, double b, double h, double cmin, double cmax);
		OrthogonalCamera(Cameraman& manager, Vector3f position, double g, double d, double b, double h, double cmin, double cmax);

		void renderProjection() const override;
	};
}