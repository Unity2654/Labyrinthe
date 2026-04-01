#include "../Maths/Vector.h"
#include <string>

namespace gloop {
	class Display {
	private:
		int wx;
		int wy;

	public:
		Display(int wx, int wy, int px, int py, std::string name);

		void reshape(int wx, int wy);

		int getSizeX() const;
		int getSizeY() const;

		void displayViewPort() const;
	};
}