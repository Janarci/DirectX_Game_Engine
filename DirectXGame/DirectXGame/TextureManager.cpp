#include "TextureManager.h"

#include <iostream>

#include "Texture.h"


TextureManager::TextureManager(): ResourceManager()
{
}


TextureManager::~TextureManager()
{
}

TexturePtr TextureManager::createTextureFromFile(const wchar_t * file_path)
{
	return std::static_pointer_cast<Texture>(createResourceFromFile(file_path));
}

Resource * TextureManager::createResourceFromFileConcrete(const wchar_t * file_path)
{
	std::wcout << file_path << std::endl;

	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}
	if (tex == nullptr)
	{
		std::wcout << "we failed" << std::endl;

	}
	return tex;
}
