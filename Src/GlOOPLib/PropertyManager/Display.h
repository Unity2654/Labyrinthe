#include "../Maths/Vector.h"
#include "../Maths/Rectangle.h"
#include <string>

namespace gloop {
	// Class storing the data of the displayed window
	class Display {
	private:
		// Dimensions of the window
		Rectangle dimensions;
		// Name of the window
		std::string name;

	public:
		Display(Rectangle dimensions, std::string name);

		// Creates a window that displays the active scene
		void createWindow();

		// Reshapes the window
		// Should be called within the glutReshape callback
		void reshape(int wx, int wy);

		// Getter for the horizontal size of the window
		int getSizeX() const;
		// Getter for the vertical size of the window
		int getSizeY() const;

		// Getter for the dimensions of the window
		const Rectangle& getDimensions() const;

		// Returns the coordinates of the center of the window
		const Vector2f getCenter() const;

		// Renders a viewport matching the size of the window
		void displayViewPort() const;
	};
}
