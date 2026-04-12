#include "GUI.h"
#include "../PropertyManager/GlPropertyManager.h"

namespace gloop {
	GUI::GUI(float sizeX, float sizeY): coordinatesSystem(sizeX, sizeY){}

	Vector2f GUI::translateCoordinates(const Vector2f& position){ 
		Vector2f abs = prop::getDisplay().getDimensions();
		return position * coordinatesSystem / abs;
	}

	void GUI::update(){
		auto& mouse = prop::getMouse();
		Vector2f mpos = translateCoordinates(mouse.getPosition());
		Vector2f mclstart = translateCoordinates(mouse.getClickStartPosition());

		//std::cout << "============" << std::endl;
		std::cout << components.size() << std::endl;
		for (auto e :components) {
			std::cout <<  "UI : " << &e << std::endl;
			e.reset();
			//std::cout << e.isEnabled() << std::endl;
			if (!e.isEnabled())
				continue;
			Rectangle cb = e.getClickBox();
			//std::cout << cb.isWithin(mpos) << std::endl;
			if (cb.isWithin(mpos)) {
				e.hover();
				//std::cout << e.isHovered() << std::endl;
				if (mouse.getState().leftButton == RELEASE) {
					if (cb.isWithin(mclstart) && cb.isWithin(mpos))
						e.click();
				}
			}
		}
		//std::cout << "============" << std::endl;
	}

	GUIElement& GUI::registerElement(const Rectangle& clickBox){
		components.push_back(GUIElement(clickBox));
		return components.back();
	}
}