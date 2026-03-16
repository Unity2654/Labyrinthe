#pragma once
#include <string>

namespace gloop {
	struct sharedTexID {
		unsigned int ID;
		int nbRef = 0;
	};

	class Texture {
	private : 
		sharedTexID& texID; // Should be effectively const
		const std::string path;

	public :

		// Constructors 
		Texture() = delete;
		Texture(std::string path);
		
		// Rule of 3
		// Preventing the use of move constructors to prevent issues with the destructor
		~Texture();
		Texture(const Texture& other);
		Texture& operator=(const Texture& other);
		Texture(const Texture&& other) = delete;
		Texture& operator=(const Texture&& other) = delete;

		// Getters
		std::string getPath() const;
		unsigned int getTextureID() const;

		// Binds the texture to use it
		void bind();

	};
}