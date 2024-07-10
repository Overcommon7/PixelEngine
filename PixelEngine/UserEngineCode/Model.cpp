#include "pch.h"
#include "Model.h"
#include "Utilities.h"

void PixelModel::Load(const string& filename)
{
	this->filename = filename;
	vector<Math::Vector3> positions;
	vector<Math::Vector3> normals;
	vector<uint32_t> normalsCount;
	vector<uint32_t> positionIndicies;

	fstream inFile(filename);
	if (!inFile.is_open())
	{
		std::cerr << "Cannot open mode file: " << filename;
		return;
	}

	while (!inFile.eof())
	{
		string buffer, line;
		getline(inFile, line);
		stringstream ss(line);
		vector<float> values(3, 0);
		ss >> buffer;
		if (buffer == "v")
		{
			short i = 0;
			while (ss.good() && i < 3)
			{
				ss >> buffer; 
				if (!Utils::TryParse(buffer, values[i]))
				{
					std::cerr << "Model Failed To Load\n";
					return;
				}
				++i;
			}
			positions.push_back({ values[0], values[1], values[2] });
		}
		else if (buffer == "f")
		{
			short i = 0;
			while (ss.good() && i < 3)
			{
				ss >> buffer;
				size_t pos = buffer.find_first_of('/');
				if (pos == string::npos || !Utils::TryParse(buffer.substr(0, pos), values[i]))
				{
					std::cerr << "Model Failed To Load\n";
					return;
				}
				++i;
			}

			positionIndicies.push_back((uint32_t)values[0]);
			positionIndicies.push_back((uint32_t)values[1]);
			positionIndicies.push_back((uint32_t)values[2]);
		}
	}

	verticies.resize(positionIndicies.size());
	normals.resize(positions.size());
	normalsCount.resize(positions.size());

	for (size_t i = 2; i < positionIndicies.size(); i += 3)
	{
		uint32_t index0 = positionIndicies[i - 2] - 1;
		uint32_t index1 = positionIndicies[i - 1] - 1;
		uint32_t index2 = positionIndicies[i] - 1;
		Math::Vector3 pos0 = positions[index0];
		Math::Vector3 pos1 = positions[index1];
		Math::Vector3 pos2 = positions[index2];
		Math::Vector3 faceNorm = (pos1 - pos0).CrossProduct((pos2 - pos0)).Normalize();
		normals[index0] = normals[index0] + faceNorm;
		normals[index1] = normals[index1] + faceNorm;
		normals[index2] = normals[index2] + faceNorm;
		++normalsCount[index0];
		++normalsCount[index1];
		++normalsCount[index2];
	}
	for (size_t i = 0; i < normals.size(); ++i)
	{
		if (normalsCount[i] > 0)
		{
			normals[i] = (normals[i] / (float)normalsCount[i]).Normalize();
		}
		else
		{
			normals[i] = Vector3(0, 0, 1);
		}
	}
	for (size_t i = 0; i < positionIndicies.size(); ++i)
	{
		verticies[i].pos = positions[positionIndicies[i] - 1];
		verticies[i].normal = normals[positionIndicies[i] - 1];
		verticies[i].color = WHITE;
	}
	inFile.close();
}

const Vertex& PixelModel::GetVertex(int idx) const
{
	return verticies[idx];
}

int PixelModel::GetVertextCount() const
{
	return (int)verticies.size();
}
