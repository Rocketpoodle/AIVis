#include "fdeepdata.h"
#include "fdeeplayer.h"

#include "fdeep/layers/layer.hpp"

namespace FdeepBridge {

Data::Data()
    : m_data_cache(std::make_shared<fdeep::internal::output_dict>())
    , m_has_valid_output(false)
{

}

std::shared_ptr<fdeep::internal::output_dict> Data::getFdeepDataCache() const
{
    return m_data_cache;
}

void Data::setValidOutput(bool valid)
{
    m_has_valid_output = valid;
}

bool Data::hasValidOutput_impl() const
{
    return m_has_valid_output;
}

void Data::clearValidOutput_impl()
{
    m_has_valid_output = false;
}

std::vector<double> Data::getLayerOutput_impl(const ModelBridge::LayerPtr& layer) const
{
    std::vector<double> outputVector;
    auto fdeepLayer = static_cast<Layer*>(layer.get())->getFdeepLayer();
    std::for_each(m_data_cache->at({layer->getId(),0}).cbegin(), m_data_cache->at({layer->getId(),0}).cend(), [&outputVector](const fdeep::internal::tensor& tensor){
        auto tensorVec = tensor.as_vector();
        std::copy(tensorVec->cbegin(), tensorVec->cend(), std::back_inserter(outputVector));
    });
    return outputVector;
}


} // namespace FdeepBridge
