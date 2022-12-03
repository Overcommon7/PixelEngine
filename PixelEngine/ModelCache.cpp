#include "pch.h"
#include "ModelCache.h"


void ModelCache::Clear()
{
	models.clear();
}

const PixelModel* ModelCache::GetModel(const string& filename)
{
	const auto iter = std::find_if(models.begin(), models.end(), [&filename](const auto& model) {
		return model->GetFileName() == filename; });
	if (iter != models.end()) return iter->get();


	auto& model = models.emplace_back(make_unique<PixelModel>());
	model->Load(filename);
	return model.get();
}


