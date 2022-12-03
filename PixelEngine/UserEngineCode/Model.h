#pragma once
#include "Vertex.h"

class PixelModel
{
public:
	void Load(const string& filename);

	const string& GetFileName() const { return filename; };
	const Vertex& GetVertex(int idx) const;
	int GetVertextCount() const;
private:
	string filename;
	vector<Vertex> verticies;
};

