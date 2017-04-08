#pragma once

#include "Byteswap.h"

// Parses an individual field.
// This is intended to be a single element in an array
// or a single element from a Boost Fusion sequence.
template <typename T>
struct FieldParser
{
  typedef FieldParser<T> type;

  static void parse(T & t)
  {
    // Would be nice to be able to set a function pointer
    // to be called to make this programmable, however,
    // not sure of a clever way to do that for compile-time.
    Byteswap::byteswap<T>(t);
  }
};


