#include "pch.h"
#include "TextureCache.h"

void TextureCache::Clear()
{
    mTextures.clear();
    mCurrentTexture = nullptr;
}

void TextureCache::SetTexture(const std::string& fileName)
{
	auto iter = std::find_if(mTextures.begin(), mTextures.end(), [&fileName](const auto& texture) {return texture->GetFileName() == fileName; });
	if (iter != mTextures.end())
	{
		mCurrentTexture = iter->get();
	}
	else
	{
		auto& texture = mTextures.emplace_back(std::make_shared<PixelTexture>());
		texture->Load(fileName);
		mCurrentTexture = texture.get();
	}
}

void TextureCache::SetAddressMode(AddressMode mode)
{
	mAddressMode = mode;
}

Math::Color TextureCache::SampleColor(Math::Color uv) const
{
	Math::Color color = uv;
	if (mCurrentTexture != nullptr && uv.b < 0.0f)
	{
		float u = uv.r / uv.a;
		float v = uv.g / uv.a;
		color = mCurrentTexture->GetPixelColor(u, v, mAddressMode);
	}
	return color;
}
