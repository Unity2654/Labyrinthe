#include "Texture.h"
#include <GL/gl.h>
#include "../../spng/spng.h" // ... I hate this
#include <iostream>

namespace gloop {
	Texture::Texture(std::string path) : texID(0), path(path){
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &texID);
		
		// Loading the image
		FILE* png;
		int ret = 0;
		spng_ctx* ctx = NULL;
		unsigned char* image = NULL;

		fopen_s(&png, path.c_str(), "rb");
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

		///////////////// TEST ///////////////// 
		ret = spng_get_ihdr(ctx, &ihdr);

		if (ret)
		{
			std::cout << "error" << std::endl;
			exit(1);
		}
		printf("width: %u\n"
			"height: %u\n"
			"bit depth: %u\n",
			ihdr.width, ihdr.height, ihdr.bit_depth, ihdr.color_type);

		printf("compression method: %u\n"
			"filter method: %u\n"
			"interlace method: %u\n",
			ihdr.compression_method, ihdr.filter_method, ihdr.interlace_method);
		///////////////// END OF TEST ///////////////// 
		unsigned int size;
		ret = spng_decoded_image_size(ctx, SPNG_FMT_PNG, &size);
		image = (unsigned char*)malloc(size);

		// Decoding the image
		ret = spng_decode_image(ctx, image, size, SPNG_FMT_RGBA8, 0);
		if (ret) {
			std::cerr << "Failed to decode image " << path << std::endl;
			exit(1);
		}
		unsigned int img_width = size / ihdr.height;
		unsigned int img_height = ihdr.height;

		// OpenGL things
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Freeing memory
		spng_ctx_free(ctx);
		free(image);
	}

	Texture::~Texture(){
	}

	Texture::Texture(const Texture& other){
	}

	Texture& Texture::operator=(const Texture& other){
		return *this;
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