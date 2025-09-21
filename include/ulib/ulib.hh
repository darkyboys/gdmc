// ulib.h
#pragma once
#include <string>
#include <vector>

namespace ulib {
    // Returns vector of {device_path, device_name}
    std::vector<std::vector<std::string>> list_input_devices();
}
