#ifndef IMPORT_EXT_DATA_MODEL_H
#define IMPORT_EXT_DATA_MODEL_H

#include <fdeep/import_model.hpp>

#include <ext_data_model_layer.h>

namespace fdeep {
namespace internal {

inline std::shared_ptr<ext_data_model_layer> create_ext_data_model_layer(const get_param_f& get_param,
                                    const nlohmann::json& data,
                                    const std::string& name, const layer_creators& custom_layer_creators,
                                    const std::string& prefix)
{
    assertion(data["config"]["layers"].is_array(), "missing layers array");

    const std::function<nlohmann::json(
        const std::string&, const std::string&)>
        get_prefixed_param = [&](const std::string& layer_name, const std::string& param_name)
        -> nlohmann::json {
        return get_param(prefix + layer_name, param_name);
    };

    const auto make_layer = [&](const nlohmann::json& json) {
        return create_layer(get_prefixed_param, json,
                            custom_layer_creators, prefix);
    };
    const auto layers = create_vector<layer_ptr>(make_layer,
                                                 data["config"]["layers"]);

    assertion(data["config"]["input_layers"].is_array(), "no input layers");

    const auto inputs = create_vector<node_connection>(
        create_node_connection, data["config"]["input_layers"]);

    const auto outputs = create_vector<node_connection>(
        create_node_connection, data["config"]["output_layers"]);

    return std::make_shared<ext_data_model_layer>(name, layers, inputs, outputs);
}

}
}
#endif // IMPORT_EXT_DATA_MODEL_H
