#ifndef LAYERINTERFACE_H
#define LAYERINTERFACE_H

#include <memory>
#include <vector>
namespace ModelBridge
{

class ModelInterface;
using ModelPtr = std::shared_ptr<ModelInterface>;
class DataInterface;
using DataPtr = std::shared_ptr<DataInterface>;

enum LayerType {
    Unknown,
    Dense
};

class LayerInterface
{
public:
    virtual std::string getId() const = 0;

    virtual LayerType getLayerType() const = 0;
};
}
#endif // LAYERINTERFACE_H
