#include "Maths/Vector.h"
#include <string>

namespace gloop {
	class Display {
	private:
		Vector2f size;

	public:
		Display(Vector2f size, Vector2f position, std::string name);

		void reshape(Vector2f size);
	};
}