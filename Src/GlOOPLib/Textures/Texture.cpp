#include "Texture.h"
#include <GL/gl.h>
#include "../../spng/spng.h" // ... I hate this
#include <iostream>

namespace gloop {

	Texture::Texture(std::string path) : path(path) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &texID);
		
		// Loading the image with spng
		FILE* png;
		int ret = 0;
		spng_ctx* ctx = NULL;
		unsigned char* image = NULL;

#if defined(WIN32) || defined(WIN64)
		int _ = fopen_s(&png, path.c_str(),"rb");
#else
		png = std::fopen(path.c_str(), "rb");
#endif
		if (png == NULL) {
			std::cerr << "Failed to load " << path << std::endl;
			exit(1);
		}
		
		ctx = spng_ctx_new(0);
		if (ctx == NULL){
			std::cerr << "Failed to create image context for " << path << std::endl;
			exit(1);
		}

		spng_set_png_file(ctx, png);
		
		struct spng_ihdr ihdr;
		ret = spng_get_ihdr(ctx, &ihdr);
		if (ret) {
			std::cerr << "Failed to decode image " << path << " : " << spng_strerror(ret) << std::endl; exit(1);
		}
		size_t size;
		ret = spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &size);
		if (ret) {
			std::cerr << "Failed to decode image " << path << " : " << spng_strerror(ret) << std::endl; exit(1);
		}
		image = (unsigned char*)malloc(size);

		// Decoding the image
		ret = spng_decode_image(ctx, image, size, SPNG_FMT_RGBA8, 0);
		if (ret) {
			std::cerr << "Failed to decode image " << path << " : " << spng_strerror(ret) << std::endl; exit(1);
		}
		unsigned int img_width = ihdr.width;
		unsigned int img_height = ihdr.height;

		// OpenGL things
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Freeing memory
		spng_ctx_free(ctx);
		free(image);
	}

	Texture::Texture(const Texture& other): texID(other.getTextureID()),path(other.getPath()) {}

	Texture::Texture(Texture&& other) {
		std::swap(other.texID, texID);
		std::swap(other.path, path);
	}

	Texture& Texture::operator=(const Texture& other){
		this->texID = other.texID;
		this->path = other.path;
		return *this;
	}

	Texture& Texture::operator=(Texture&& other){
		std::swap(other.texID, texID);
		std::swap(other.path, path);
		return *this;
	}

	const std::string Texture::getPath() const{
		return std::string();
	}

	unsigned int Texture::getTextureID() const{
		return texID;
	}

	void Texture::bind() const{
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	void Texture::unbind() const{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	std::map <std::string, Texture> TextureManager::loadedTextures{};

	Texture TextureManager::load(const std::string path) {
		auto tex = loadedTextures.find(path);
		if (tex != loadedTextures.end()) {
			return Texture(tex->second);
		}
		Texture t = Texture(path);
		loadedTextures.emplace(path, t);
		return t;
	}
}
