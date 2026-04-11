#include "GUI.h"
#include "../PropertyManager/GlPropertyManager.h"

namespace gloop {

	void GUI::update(){
		auto& mouse = prop::getMouse();
		Vector2f mpos = mouse.getPosition();

		for (auto& e : components) {
			e.reset();
			if (!e.isEnabled())
				continue;
			Rectangle cb = e.getClickBox();
			if (cb.isWithin(mpos)) {
				e.hover();
				if (mouse.getState().leftButton == RELEASE) {
					if (cb.isWithin(mouse.getClickStartPosition()) && cb.isWithin(mpos))
						e.click();
				}
			}
		}
	}
}