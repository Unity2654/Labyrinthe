#include "GUIElement.h"

namespace gloop {

	GUIElement::GUIElement(Rectangle clickBox) : clickBox(clickBox){}

	bool GUIElement::isHovered() const{
		return hovered;
	}

	bool GUIElement::isClicked() const{
		return clicked;
	}

	bool GUIElement::isEnabled() const{
		return enabled;
	}

	const Rectangle& GUIElement::getClickBox() const{
		return clickBox;
	}

	void GUIElement::hover(){
		hovered = true;
	}

	void GUIElement::click(){
		clicked = true;
	}

	void GUIElement::enable(){
		enabled = true;
	}

	void GUIElement::disable(){
		enabled = false;
	}

	bool GUIElement::toggle(){
		enabled = !enabled;
		return enabled;
	}

	void GUIElement::reset(){
		clicked = false;
		hovered = false;
	}
}
