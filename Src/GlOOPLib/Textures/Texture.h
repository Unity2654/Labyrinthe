#pragma once
#include <string>
#include <memory>
#include <map>

namespace gloop {

	// Class storing the main properties of a texture
	class Texture {
	private : 
		// ID of the texture
		unsigned int texID = 0;
		// Path to the texture
		std::string path;

	public :

		// Constructors 
		Texture() = delete;
		Texture(std::string path);
		Texture(const Texture& other);
		Texture(Texture&& other);

		Texture& operator=(const Texture& other);
		Texture& operator=(Texture&& other);

		// Returns the path to the image of the texture
		const std::string getPath() const;
		// Returns the ID of the texture
		unsigned int getTextureID() const;

		// Binds the texture to use it
		void bind() const;
		// UnBinds the texture
		void unbind() const;

	};

	// Static subclass allowing an easier management of the textures
	class TextureManager {
	private :
		static std::map<std::string, Texture> loadedTextures;

	public:
		TextureManager() = delete;

		// Loads a texture from its path
		// If the texture has already been loaded, returns it instead of creating a new one
		static Texture load(std::string path);
	};
}