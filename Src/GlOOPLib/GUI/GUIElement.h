#pragma once
#include "../Maths/Rectangle.h"

/* An element that's part of a graphic user interface
*  It contains a "clickbox" defining a rectangular zone in screen coordinates. 
*  If the user's mouse is located in this area, the element will be considered to be "hovered".
*  If the user clicks in this area, the element will be considered to be "clicked".
* 
*  Those states are reset in each frame, and updated through it.
* 
*  GUI elements are not rendered, and are only there to detect user's clicks in given area, and help other components of the app react to it.
* 
*  GUI elements can be enabled or disabled at will.
*  The interpretation of this state is done outside of this class.
*/
namespace gloop {

	class GUIElement {
	private :
		const Rectangle clickBox;
		bool clicked = false;
		bool hovered = false;

		bool enabled = true;

	public :

		GUIElement(Rectangle clickBox);

		// Getters
		bool isHovered() const;
		bool isClicked() const;

		bool isEnabled() const;

		const Rectangle& getClickBox() const;

		// Updates of the element's state
		void hover();
		void click();

		void enable();
		void disable();
		bool toggle();

		/** 
		 * Resets the state of the element (the element is not hovered nor clicked)
		 */
		void reset();
	};
}