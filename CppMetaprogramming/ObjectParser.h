#pragma once

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits.hpp>

#include "FieldParser.h"

namespace Parser
{

  // Forward declaration for ObjectParser.
  template <typename T> struct ObjectParser;

  // Parses an array.
  template <typename T>
  struct ArrayParser
  {
    typedef ArrayParser<T> type;

    // Slice the front-most dimension of an array.
    // For example char array[3][2][6] would be [3] then [2]
    // then [6] leading to parsing each value.
    typedef typename boost::remove_bounds<T>::type slice;
    static const size_t size = sizeof(T) / sizeof(slice);

    static void parse(T & arr)
    {
      for (size_t i = 0; i < size; ++i)
      {
        ObjectParser<slice>::parse(arr[i]);
      }
    }
  };

  // Parses a Boost Fusion sequence.
  // Template parameters
  // Sequence is the Boost Fusion sequence to be examined
  // N is the index into the sequence (boost::mpl::int_<>)
  // See reference for boost::mpl::at as example:
  // http://www.boost.org/doc/libs/1_31_0/libs/mpl/doc/ref/Reference/at.html
  template <typename Sequence, typename N>
  struct SequenceIter
  {
    // Next field in the sequence.  
    typedef typename boost::mpl::next<N>::type next;

    // Current field in the sequence.
    typedef typename boost::fusion::result_of::value_at<Sequence, N>::type current;

    static void parse(Sequence & seq)
    {
      ObjectParser<current>::parse(boost::fusion::at<N>(seq));
      SequenceIter<Sequence, next>::parse(seq);
    }
  };

  // Provide nested name specifier "type", allows for visiting each field in 
  // a Boost Fusion sequence.
  template <typename Sequence>
  struct SequenceIter<Sequence, typename boost::fusion::result_of::size<Sequence>::type>
  {
    static void parse(Sequence & seq)
    {
      // Do nothing, all parsing is handled by the above SequenceIter.
    }
  };

  // Kicks off sequence parsing.
  template <typename Sequence>
  struct SequenceParser {
    typedef typename SequenceParser<Sequence> type;

    static void parse(Sequence & seq)
    {
      SequenceIter<Sequence, boost::mpl::int_<0>>::parse(seq);
    };
  };

  // Determines the type to parse. Checks if it is a Boost Fusion sequence or an
  // array otherwise it is treated as a field.
  template <typename T> struct TypeParser {
    typedef typename boost::mpl::eval_if<
        boost::fusion::traits::is_sequence<T>,
        SequenceParser<T>,                      // sequence
      typename boost::mpl::eval_if<
        boost::is_array<T>,                     // array
        boost::mpl::identity<ArrayParser<T>>,
      FieldParser<T>>>::type type;              // field
  };

  // Initiates parsing of an object.
  template <typename T>
  struct ObjectParser : public TypeParser<T>::type
  {

  };

}
