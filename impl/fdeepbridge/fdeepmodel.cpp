#include "fdeepmodel.h"

#include "FdeepInternalRep.h"
#include "fdeepdata.h"
#include "layers/fdeeplayerifacefactory.h"

using namespace FdeepBridge;

Model::Model(const fdeep::ext_data_model& model)
    : m_model_ptr(std::make_unique<fdeep::ext_data_model>(model))
{
    std::transform(m_model_ptr->get_model()->get_layers().cbegin(),
                   m_model_ptr->get_model()->get_layers().cend(),
                   std::back_inserter(m_layers),
                   [](const fdeep::internal::layer_ptr& a) -> LayerPtr {
        return FdeepLayerFactorySingleton::instance().createBridgeInterface(a);
    });
}

void Model::apply_impl(ModelBridge::DataPtr& data) const
{
    auto theData = static_cast<Data*>(data.get())->getFdeepDataCache();
    auto inputShape = getInputShape();
    int totalSize = std::accumulate(inputShape.cbegin(), inputShape.cend(), 1, [](const int& a, const int& b){
        return a*b;
    });
    /*! \todo: don't assume shape is size 1 */
    fdeep::internal::float_vec values;
    std::copy(data->getInputs().cbegin(), data->getInputs().cend(), std::back_inserter(values));
    fdeep::internal::tensors input;
    std::vector<std::size_t> dimensions(inputShape.size());
    std::transform(inputShape.cbegin(), inputShape.cend(), dimensions.begin(), [](const int& dim){return dim;});
    input.emplace_back(fdeep::internal::create_tensor_shape_from_dims(dimensions), std::move(values));
    m_model_ptr->predict_ext(input, *theData);
    static_cast<Data*>(data.get())->setValidOutput(true);
}

const std::vector<LayerPtr>& Model::getLayers() const
{
    return m_layers;
}

std::vector<LayerPtr> Model::getIncomingLayers(const LayerPtr& layer) const
{
    auto foundLayer = std::find_if(m_layers.cbegin(), m_layers.cend(), [&layer](const LayerPtr& a){
        return a->getId() == layer->getId();
    });

    if (foundLayer == m_layers.cend()) {
        return {};
    }

    auto fdeepLayer = std::static_pointer_cast<FdeepInternalRep>(layer->getInternalRep())->getLayerPtr();

    // for each node in this layer, check all incoming nodes and append the layers to the incomingLayers vector
    std::vector<LayerPtr> incomingLayers;
    std::for_each(fdeepLayer->nodes_.cbegin(),
                  fdeepLayer->nodes_.cend(),
                  [&](const fdeep::internal::node& a){
                      std::for_each(a.inbound_connections_.cbegin(),
                                    a.inbound_connections_.cend(),
                                    [&](const fdeep::internal::node_connection& b){
                                        // this should always find the given layer
                                        LayerPtr foundLayer = *std::find_if(m_layers.cbegin(), m_layers.cend(), [&](const LayerPtr& checkLayer){
                                            return checkLayer->getId() == b.layer_id_;
                                        });
                                        // only append if unique
                                        if(std::find(incomingLayers.cbegin(), incomingLayers.cend(), foundLayer) == incomingLayers.cend())  {
                                            incomingLayers.push_back(foundLayer);
                                        }
                                    });
                      });
    return incomingLayers;
}

std::vector<int> Model::getInputShape() const
{
    /*! \todo: don't assume shape is size 1 */
    return getTensorShapeAsVector(*m_model_ptr->get_input_shapes().begin());
}

std::vector<int> Model::getOutputShape() const
{
    /*! \todo: don't assume shape is size 1 */
    return getTensorShapeAsVector(*m_model_ptr->get_output_shapes().begin());
}

std::vector<int> FdeepBridge::getTensorShapeAsVector(const fdeep::internal::tensor_shape_variable& shape)
{
    std::vector<int> outputShape(shape.rank(),0);
    switch (shape.rank())
    {
    case 5:
        outputShape[4] = shape.size_dim_5_.unsafe_get_just();
    case 4:
        outputShape[3] = shape.size_dim_4_.unsafe_get_just();
    case 3:
        outputShape[2] = shape.height_.unsafe_get_just();
    case 2:
        outputShape[1] = shape.width_.unsafe_get_just();
    case 1:
        outputShape[0] = shape.depth_.unsafe_get_just();
    }
    return outputShape;
}
