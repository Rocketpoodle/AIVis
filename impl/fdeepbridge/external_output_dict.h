#ifndef EXTERNAL_OUTPUT_DICT_H
#define EXTERNAL_OUTPUT_DICT_H

#include <fdeep/layers/layer.hpp>

namespace fdeep {
namespace internal {

class ext_data_model_layer;

class external_output_dict
{
public:

    external_output_dict()
        : valid_(false)
    {

    }

    inline void set_valid(bool valid)
    {
        valid_ = valid;
    }

    inline bool get_valid() const
    {
        return valid_;
    }

    inline tensor get_output(const node_connection& conn, const layer_ptrs& layers )
    {
        return get_layer(layers, conn.layer_id_)->get_output(layers, output_cache_, conn.node_idx_, conn.tensor_idx_);
    }

    output_dict& get_output_dict()
    {
        return output_cache_;
    }

private:
    output_dict output_cache_;
    bool valid_;
};

}
}


#endif // EXTERNAL_OUTPUT_DICT_H
