#ifndef SETS_01_BASICS_08_DETECT_AES_IN_ECB_MODE_HPP_INCLUDED
#define SETS_01_BASICS_08_DETECT_AES_IN_ECB_MODE_HPP_INCLUDED

#include <string> // std::string
#include <vector> // std::vector

#include "utils/types.hpp" // byte

namespace s01
{
    namespace c08
    {
        std::string detect_aes_in_ecb_mode(std::string& file_path);
    };
};

#endif /* SETS_01_BASICS_08_DETECT_AES_IN_ECB_MODE_HPP_INCLUDED */
