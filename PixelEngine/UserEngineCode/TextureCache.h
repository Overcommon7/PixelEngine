#pragma once
#include "Texture.h"

class TextureCache
{
    TextureCache() = delete;
    TextureCache(const TextureCache& t) = delete;
    TextureCache& operator=(const TextureCache& t) = delete;

	std::vector<std::shared_ptr<PixelTexture>> mTextures;
	const PixelTexture* mCurrentTexture = nullptr;
	AddressMode mAddressMode = AddressMode::Clamp;

public:
	void Clear();
	void SetTexture(const std::string& fileName);
	void SetAddressMode(AddressMode mode);

	Math::Color SampleColor(Math::Color uv) const;


};
