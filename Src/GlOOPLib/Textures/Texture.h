#pragma once
#include <string>
#include <memory>

namespace gloop {

	class Texture {
	private : 
		unsigned int texID = 0;
		const std::string path;

	public :

		// Constructors 
		Texture() = delete;
		Texture(std::string path);

		// Getters
		std::string getPath() const;
		unsigned int getTextureID() const;

		// Binds the texture to use it
		void bind() const;

	};
}