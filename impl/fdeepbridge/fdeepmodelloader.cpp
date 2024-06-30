#include "public/fdeepmodelloader.h"

#include "ext_data_model.h"
#include "fdeepmodel.h"

FdeepModelLoader::FdeepModelLoader() {}

ModelBridge::ModelPtr FdeepModelLoader::loadModelFromFile(const std::string& filePath) const
{
    auto fdeep_model = fdeep::load_ext_data_model(filePath);
    auto model = std::make_shared<FdeepBridge::Model>(fdeep_model);
    model->initialize();
    return model;
}

std::list<std::string> FdeepModelLoader::getModelFileFilters() const
{
    return {"*.json"};
}
