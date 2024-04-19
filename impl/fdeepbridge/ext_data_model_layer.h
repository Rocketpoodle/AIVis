#ifndef EXT_DATA_MODEL_LAYER_H
#define EXT_DATA_MODEL_LAYER_H

#include <fdeep/layers/layer.hpp>

#include "external_output_dict.h"

namespace fdeep {
namespace internal {

class ext_data_model_layer : public layer
{
public:
    explicit ext_data_model_layer(const std::string& name,
                       const layer_ptrs& layers,
                       const node_connections& input_connections,
                       const node_connections& output_connections)
        : layer(name)
        , layers_(layers)
        , input_connections_(input_connections)
        , output_connections_(output_connections)
    {
        assertion(fplus::all_unique(
                      fplus::transform(fplus_get_ptr_mem(name_), layers)),
                  "layer names must be unique");
    }

    tensors apply_ext(const tensors& input, output_dict& output_cache) const
    {
        const auto result = apply_ext_impl(input, output_cache);
        if (activation_ == nullptr)
            return result;
        else
            return apply_activation_layer(activation_, result);
    }
    tensor get_output(const layer_ptrs& layers, output_dict& output_cache,
                      std::size_t node_idx, std::size_t tensor_idx) const override
    {
        // https://stackoverflow.com/questions/46011749/understanding-keras-model-architecture-node-index-of-nested-model
        node_idx = node_idx - 1;
        assertion(node_idx < nodes_.size(), "invalid node index");
        return layer::get_output(layers, output_cache, node_idx, tensor_idx);
    }
    void reset_states() override
    {
        for (const auto& single_layer : layers_) {
            single_layer->reset_states();
        }
    }
    bool is_stateful() const override
    {
        return fplus::any_by([](const auto& single_layer) {
            return single_layer->is_stateful();
        },
                             layers_);
    }
    const layer_ptrs& get_layers() const
    {
        return layers_;
    }
protected:
    tensors apply_ext_impl(const tensors& inputs, output_dict& output_cache) const
    {
        assertion(inputs.size() == input_connections_.size(),
                  "invalid number of input tensors for this model: " + fplus::show(input_connections_.size()) + " required but " + fplus::show(inputs.size()) + " provided");

        for (std::size_t i = 0; i < inputs.size(); ++i) {
            output_cache[input_connections_[i].without_tensor_idx()] = { inputs[i] };
        }

        const auto get_output = [this, &output_cache](const node_connection& conn) -> tensor {
            return get_layer(layers_, conn.layer_id_)->get_output(layers_, output_cache, conn.node_idx_, conn.tensor_idx_);
        };
        auto outputs = fplus::transform(get_output, output_connections_);

        return outputs;
    }

    tensors apply_impl(const tensors& inputs) const override
    {
        output_dict output_cache;

        assertion(inputs.size() == input_connections_.size(),
                  "invalid number of input tensors for this model: " + fplus::show(input_connections_.size()) + " required but " + fplus::show(inputs.size()) + " provided");

        for (std::size_t i = 0; i < inputs.size(); ++i) {
            output_cache[input_connections_[i].without_tensor_idx()] = { inputs[i] };
        }

        const auto get_output = [this, &output_cache](const node_connection& conn) -> tensor {
            return get_layer(layers_, conn.layer_id_)->get_output(layers_, output_cache, conn.node_idx_, conn.tensor_idx_);
        };
        return fplus::transform(get_output, output_connections_);
    }
    layer_ptrs layers_;
    node_connections input_connections_;
    node_connections output_connections_;
};

}
}


#endif // EXT_DATA_MODEL_LAYER_H
