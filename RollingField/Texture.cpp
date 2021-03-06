#include "Texture.h"
#include "Err.h"
#include <GL/glu.h>
#include <SDL_Image.h>
#include "assert.h"

Texture::Texture()
{
    textureId = -1;
}

bool Texture::LoadTexture(const std::string& filename)
{

	SDL_Surface* surf = IMG_Load(filename.c_str());
	
	CreateFromSDLSurface(surf);

    SDL_FreeSurface(surf);

    return true;
}

bool Texture::CreateFromSDLSurface(SDL_Surface* surf)
{
	glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if (!surf)
	{
		Err::Log("Surface pointer invalid while creating Texture");
		return false;
	}
	unsigned char* data = (unsigned char*)surf->pixels;
	int width = surf->w;
	int height = surf->h;

    if (surf->format->BytesPerPixel == 3)
    {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data);

        gluBuild2DMipmaps(
            GL_TEXTURE_2D,  
            GL_RGB,
            width,
            height,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data);
    }
    else if (surf->format->BytesPerPixel == 4)
    {
        glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);

        gluBuild2DMipmaps(
            GL_TEXTURE_2D,
            GL_RGBA,
            width,
            height,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data);
    }
    else
    {
        // Unexpected format
		Err::Log("Surface depth invalid while creating Texture");
        assert(0);
    }
	return true;
}

Texture::~Texture()
{
    if (textureId > -1)
    {
    	glDeleteTextures(1, &textureId);
    }
}

void Texture::UseThisTexture()
{
	glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureId);
}

