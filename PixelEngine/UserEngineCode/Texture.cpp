#include "pch.h"
#include "Texture.h"

namespace
{
#pragma pack(push, 1)
	struct BitmapFileHeader
	{
		uint16_t type;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t size;
		uint32_t offset;
	};

	struct BitmapInfoHeader
	{
		uint32_t size;
		int width, height;
		uint16_t planes;
		uint16_t bits;
		uint32_t compression;
		uint32_t imageSize;
		int xResolution, yResolution;
		uint32_t numColors;
		uint32_t importantColors;
	};

	static uint32_t MakeStringAligned(uint32_t rowStride, uint32_t alignStride)
	{
		uint32_t newStride = rowStride;
		while (newStride % alignStride != 0)
		{
			newStride++;
		}

		return newStride;
	}
#pragma pack(pop)
}

void PixelTexture::Load(const string& filename)
{
	ifstream inFile(filename, std::ios::binary);
	if (!inFile.is_open())
		return;

	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;
	string buffer;
	
	buffer.resize(sizeof(BitmapFileHeader));
	inFile.read(&buffer.front(), sizeof(BitmapFileHeader));
	fileHeader = *(BitmapFileHeader*)buffer.c_str();
	buffer.clear();
	buffer.resize(sizeof(BitmapInfoHeader));
	inFile.read(&buffer.front(), sizeof(BitmapInfoHeader));
	infoHeader = *(BitmapInfoHeader*)buffer.c_str();

	if (infoHeader.bits != 24)
	{
		inFile.close();
		return;
	}

	width = infoHeader.width;
	height = infoHeader.height;

	pixels = make_unique<Math::Color[]>(width * height);

	inFile.seekg(fileHeader.offset);

	auto rowStride = width * infoHeader.bits / 8;
	auto paddedStride = MakeStringAligned(rowStride, 4);
	vector<uint8_t> paddingBytes(paddedStride - rowStride);

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uint8_t r, g, b;
			buffer.clear();
			buffer.resize(sizeof(uint8_t));
			inFile.read(&buffer.front(), sizeof(uint8_t));
			r = *(uint8_t*)buffer.c_str();
			buffer.clear();
			inFile.read(&buffer.front(), sizeof(uint8_t));
			g = *(uint8_t*)buffer.c_str();
			buffer.clear();
			inFile.read(&buffer.front(), sizeof(uint8_t));
			b = *(uint8_t*)buffer.c_str();
			buffer.clear();
			uint32_t index = i + ((height - j - 1) * width);
			pixels[index] =  Math::Color(r, g, b);
		}
		inFile.read((char*)paddingBytes.data(), paddingBytes.size());
	}
	inFile.close();
}

Math::Color PixelTexture::GetPixelColor(float u, float v, AddressMode mode) const
{
	int uIndex = (int)(u * (width - 1));
	int vIndex = (int)(v * (height - 1));

	switch (mode)
	{
	case AddressMode::Clamp:
		uIndex = std::clamp(uIndex, 0, width - 1);
		vIndex = std::clamp(vIndex, 0, height - 1);
		break;
	case AddressMode::Wrap:
		uIndex %= width;
		vIndex %= height;
		break;
	}

	return pixels[(uIndex + vIndex) * width];
}
