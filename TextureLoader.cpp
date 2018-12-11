#include "TextureLoader.h"

#include <stdio.h>


TextureLoader::TextureLoader(SDL_Renderer * r)
{
	myRenderer = r;
}


TextureLoader::~TextureLoader()
{
	flush();
}


Texture * TextureLoader::load(std::string file)
{
	auto search = myTextureMap.find(file);
	if (search == myTextureMap.end())
	{
		Texture * newTexture = new Texture();
		bool success = newTexture->loadFromFile(file, myRenderer);
		if (!success)printf("Loading image %s failed", file.c_str());
		myTextureMap[file] = newTexture;
		return newTexture;
	}
	else
	{
		return search->second;
	}
}


void TextureLoader::flush()
{
	for (auto i = myTextureMap.begin(); i != myTextureMap.end(); i++)
	{
		delete i->second;
	}
	myTextureMap.clear();
}