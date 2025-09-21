// ulib.cpp
#include "ulib.hh"
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <cstring>
#include <iostream>

namespace ulib {

std::vector<std::vector<std::string>> list_input_devices() {
    std::vector<std::vector<std::string>> devices;

    const char* dev_path = "/dev/input";
    DIR* dir = opendir(dev_path);
    if (!dir) return devices;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name(entry->d_name);

        // Only consider event devices
        if (name.find("event") != 0) continue;

        std::string full_path = std::string(dev_path) + "/" + name;

        int fd = open(full_path.c_str(), O_RDONLY);
        if (fd < 0) continue;

        char device_name[256] = "Unknown";
        if (ioctl(fd, EVIOCGNAME(sizeof(device_name)), device_name) < 0) {
            std::strcpy(device_name, "Unknown");
        }

        devices.push_back({full_path, std::string(device_name)});
        close(fd);
    }

    closedir(dir);
    return devices;
}

} // namespace ulib
