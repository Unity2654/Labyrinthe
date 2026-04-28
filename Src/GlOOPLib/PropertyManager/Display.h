#include "../Maths/Vector.h"
#include "../Maths/Rectangle.h"
#include <string>

namespace gloop {
	class Display {
	private:
		Rectangle dimensions;
		std::string name;

	public:
		Display(Rectangle dimensions, std::string name);

		void createWindow();

		void reshape(int wx, int wy);

		int getSizeX() const;
		int getSizeY() const;

		const Rectangle& getDimensions() const;

		const Vector2f& getCenter() const;

		void displayViewPort() const;
	};
}
