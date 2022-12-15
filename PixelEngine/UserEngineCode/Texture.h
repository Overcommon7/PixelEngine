#pragma once

enum class AddressMode : int
{
	Clamp,
	Wrap
};

class PixelTexture
{
public :
	void Load(const string& filename);
	const string& GetFileName() const { return filename; }
	Math::Color GetPixelColor(float u, float v, AddressMode mode) const;

private:
	string filename;
	unique_ptr<Math::Color[]> pixels;
	int width = 0;
	int height = 0;

};

