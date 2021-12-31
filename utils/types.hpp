#ifndef UTILS_TYPES_HPP_INCLUDED
#define UTILS_TYPES_HPP_INCLUDED

/* types */
using BYTE = unsigned char; // TODO: is 'BYTE' the right name here?
using BIT = unsigned char;
using uint = unsigned int; // Redefine in case the compiler already defines it

/* types's metrics */
const int BYTE_NUM_OF_BITS = 8;
const int POSSIBLE_BYTES_NUM = 1 << 8;

#endif /* UTILS_TYPES_HPP_INCLUDED */
