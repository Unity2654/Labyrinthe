#include "Texture.h"

namespace gloop {
	Texture::Texture(std::string path){
	}

	Texture::~Texture(){
	}

	Texture::Texture(const Texture& other){
	}

	Texture& Texture::operator=(const Texture& other){
		// TODO: insérer une instruction return ici
	}

	std::string Texture::getPath() const{
		return std::string();
	}

	unsigned int Texture::getTextureID() const{
		return 0;
	}

	void Texture::bind(){
	}
}