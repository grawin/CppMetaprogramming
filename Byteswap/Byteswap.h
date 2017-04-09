#pragma once

namespace Byteswap {

  void byteswap16(void * value);
  void byteswap32(void * value);

  template<typename T>
  void byteswap(T & t)
  {
    // Do nothing.
  }

  template<>
  void byteswap(int & x)
  {
    byteswap32(&x);
  }

  template<>
  void byteswap(unsigned int & x)
  {
    byteswap32(&x);
  }

  template<>
  void byteswap(long & x)
  {
    byteswap32(&x);
  }

  template<>
  void byteswap(unsigned long & x)
  {
    byteswap32(&x);
  }

  template<>
  void byteswap(short & x)
  {
    byteswap16(&x);
  }

  template<>
  void byteswap(unsigned short & x)
  {
    byteswap16(&x);
  }

  void byteswap16(void * value)
  {
    unsigned short & x = *(unsigned short *)value;

    // Swap upper and lower bytes
    x = ((x & 0xff) << 8) | ((x & 0xff00) >> 8);
  }

  void byteswap32(void * value)
  {
    unsigned long & x = *(unsigned long *)value;

    // Byte 3 to 0, byte 1 to 2, byte 2 to 1, byte 0 to 3
    x = ((x >> 24) & 0xff) |
      ((x << 8) & 0xff0000) |
      ((x >> 8) & 0xff00) |
      ((x << 24) & 0xff000000);
  }

}
