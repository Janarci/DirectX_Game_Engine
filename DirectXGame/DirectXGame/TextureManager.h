#pragma once
#include <memory>

#include "ResourceManager.h"
#include "Texture.h"

typedef std::shared_ptr<Texture> TexturePtr;

class TextureManager: public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	TexturePtr createTextureFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};

