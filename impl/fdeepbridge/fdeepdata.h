#ifndef FDEEPBRIDGE_DATA_H
#define FDEEPBRIDGE_DATA_H

#include <DataInterface.h>
#include <fdeep/node.hpp>

namespace FdeepBridge {

class Data : public ModelBridge::DataInterface
{
public:
    Data();

    std::shared_ptr<fdeep::internal::output_dict> getFdeepDataCache() const;

    void setValidOutput(bool valid);

protected:
    bool hasValidOutput_impl() const override;
    void clearValidOutput_impl() override;
    virtual std::vector<double> getLayerOutput_impl(const ModelBridge::LayerPtr& layer) const override;

private:
    std::shared_ptr<fdeep::internal::output_dict> m_data_cache;

    bool m_has_valid_output;
};

} // namespace FdeepBridge

#endif // FDEEPBRIDGE_DATA_H
