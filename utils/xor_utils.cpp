#include "xor_utils.hpp"


char xor_utils::xor_char_bits(char bit1, char bit2)
{
    return ((bit1 - '0') ^ (bit2 - '0')) + '0';
}    
