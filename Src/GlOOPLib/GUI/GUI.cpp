#include "GUI.h"
#include "../PropertyManager/GlPropertyManager.h"

namespace gloop {
	GUI::GUI(float sizeX, float sizeY): coordinatesSystem(sizeX, sizeY){}

	Vector2f GUI::translateCoordinates(const Vector2f& position){ 
		const Rectangle& dim = prop::getDisplay().getDimensions();
		Vector2f abs = dim.getDiagonal();
		float ratio = coordinatesSystem.x / coordinatesSystem.y;
		float absratio = abs.x / abs.y;
		Vector2f offset = { (abs.x - abs.y * ratio) / 2, 0.0 };
		if (absratio > ratio) {
			abs.x = abs.y / ratio;
		}
		else if (absratio < ratio) {
			abs.x = ratio * abs.y;
		}
		return (position-offset) * coordinatesSystem / abs;
	}

	void GUI::update(){
		auto& mouse = prop::getMouse();
		Vector2f mpos = translateCoordinates(mouse.getPosition());
		Vector2f mclstart = translateCoordinates(mouse.getClickStartPosition());

		for (auto e :components) {
			e->reset();
			if (!e->isEnabled())
				continue;
			Rectangle cb = e->getClickBox();
			if (cb.isWithin(mpos)) {
				e->hover();
				if (mouse.getState().leftButton == RELEASE) {
					if (cb.isWithin(mclstart) && cb.isWithin(mpos))
						e->click();
				}
			}
		}
	}

	std::shared_ptr<GUIElement> GUI::registerElement(const Rectangle& clickBox){
		components.push_back(std::make_shared<GUIElement>(GUIElement(clickBox)));
		return components.back();
	}
}