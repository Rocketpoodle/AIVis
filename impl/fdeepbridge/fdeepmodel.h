#ifndef FDEEPMODEL_H
#define FDEEPMODEL_H

#include <ModelInterface.h>
#include "ext_data_model.h"

namespace FdeepBridge {

using LayerPtr = ModelBridge::LayerPtr;

class Model : public ModelBridge::ModelInterface
{
public:
    Model(const fdeep::ext_data_model& model);
    std::vector<int> getInputShape() const override;
    std::vector<int> getOutputShape() const override;

protected:
    virtual void apply_impl(ModelBridge::DataPtr& data) const override;
    virtual const std::vector<LayerPtr>& getLayers() const override;
    virtual std::vector<LayerPtr> getIncomingLayers(const LayerPtr& layer) const override;

private:
    std::unique_ptr<fdeep::ext_data_model> m_model_ptr;
    std::vector<LayerPtr> m_layers;
};

std::vector<int> getTensorShapeAsVector(const fdeep::internal::tensor_shape_variable& shape);
}
#endif // FDEEPMODEL_H
