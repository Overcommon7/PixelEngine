#pragma once
#include "Model.h"

class ModelCache
{
    ModelCache() = delete;
    ModelCache(const ModelCache& m) = delete;
    ModelCache& operator=(const ModelCache& m) = delete;

    inline static vector<unique_ptr<PixelModel>> models = {};
public:

    static void Clear();
    static const PixelModel* GetModel(const string& filename);
};

