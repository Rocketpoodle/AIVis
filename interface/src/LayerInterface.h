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

/*!
 * \brief The InternalLayerRep class
 * \details interface for internal representation, to be used for layers that need access
 *          to layer specific parameters by the ViewModel
 */
class InternalLayerRep {};

/*!
 * \brief The LayerInterface class
 * \details Interface between the layer ViewModel and underlying model layer representation
 */
class LayerInterface
{
public:
    // gets layer id string, unique for each layer in the model
    virtual std::string getId() const = 0;

    // gets layer type string, identifying the layer type to match with View/ViewModel layer types
    virtual std::string getLayerType() const = 0;

    // gets internal layer representation interface for the layer
    virtual std::shared_ptr<InternalLayerRep> getInternalRep() const = 0;
};
}
#endif // LAYERINTERFACE_H
