#include "SceneProperties.h"
#include <GL/gl.h>

namespace gloop {
	void SceneProperties::toggleTexures(){
		textures = !textures;
	}

	void SceneProperties::toggleLights(){
		lights = !lights;
	}

	void SceneProperties::display(){
		if(lights)
			glEnable(GL_LIGHTING);
		else
			glDisable(GL_LIGHTING);
		if (textures)
			glEnable(GL_TEXTURE_2D);
		else
			glDisable(GL_TEXTURE_2D);
	}



}
