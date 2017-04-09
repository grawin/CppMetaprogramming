# CppMetaprogramming
C++ metaprogramming playground

Yet another sandbox type project. This time for some C++ metaprogramming, more specifically [template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming) using the [Boost](http://www.boost.org/) Fusion/MPL libraries.

## Contents
### Byteswap
Sample code that attempts to add reflection to C++ using Boost `BOOST_FUSION_ADAPT_STRUCT` this allows for iterating over the members of a structure. In the example, structures can be traversed and byteswapping is performed on any 16-bit or 32-bit integral values.

### ByteswapTest
Simple test harness using Google Test to do an end-to-end test of the object parser -> byte swapper.

## Environment
Visual Studio Community 2015
 * My current project setup uses Nuget package manager to pull Google Test and Boost
 #### Manual Setup
 * Download and extract Google Test add it to "additional include directories" and libraries
 * Download and extract Boost and add it to "additional include directories"
   * If using Linux, install Boost using your OS's package manager, it should default to usr/include and usr/lib64
 * No need to build Boost for this project (just the headers are needed)
