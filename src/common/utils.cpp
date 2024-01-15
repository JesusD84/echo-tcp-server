// utils.cpp

#include <common/utils.hpp>

namespace Utils {
    void printMessage(const std::string& prefix, const std::string& message) {
        std::cout << "[" << prefix << "] " << message << std::endl;
    }
}
