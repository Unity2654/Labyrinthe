#pragma once
#include <string>

namespace gloop {
	class Texture {
	private : 
		unsigned int texID; // Should be effectively const
		const std::string path;
		int ctr = 0;

	public :

		// Constructors 
		Texture() = delete;
		Texture(std::string path);
		
		// Rule of 3
		// Please don't use move constructor/assignment operator with this object
		~Texture();
		Texture(const Texture& other);
		Texture& operator=(const Texture& other);

		// Getters
		std::string getPath() const;
		unsigned int getTextureID() const;

		// Binds the texture to use it
		void bind();

	};
}