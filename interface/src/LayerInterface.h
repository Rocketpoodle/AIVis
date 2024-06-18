#ifndef LAYERINTERFACE_H
#define LAYERINTERFACE_H

#include <memory>
#include <string>

namespace ModelBridge
{

class ModelInterface;
using ModelPtr = std::shared_ptr<ModelInterface>;
class DataInterface;
using DataPtr = std::shared_ptr<DataInterface>;

class InternalLayerRep {};

class LayerInterface
{
public:
    virtual std::string getId() const = 0;

    virtual std::string getLayerType() const = 0;

    virtual std::shared_ptr<InternalLayerRep> getInternalRep() const = 0;
};
}
#endif // LAYERINTERFACE_H
