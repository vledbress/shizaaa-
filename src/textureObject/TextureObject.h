#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <memory>




class TextureObject {
private:
	GLuint textureID = 0;
	int width, height, nChannels;
public:
	TextureObject(unsigned char* data, int width, int height, int chanels);
	~TextureObject();
	void use();
};



typedef std::shared_ptr<TextureObject> ptrToTO;


