#ifndef ITEROPS_H
#define ITEROPS_H

#include <iterator>
#include <type_traits>

template <class Iterator>
Iterator Advance(Iterator& it, typename std::iterator_traits<Iterator>::difference_type step) {
  if constexpr (std::is_same_v<std::random_access_iterator_tag,
                               typename std::iterator_traits<Iterator>::iterator_category>) {
    return it += step;
  }
  if constexpr (std::is_same_v<std::bidirectional_iterator_tag,
                               typename std::iterator_traits<Iterator>::iterator_category>) {
    if (step < 0) {
      while (step) {
        --it;
        ++step;
      }
      return it;
    }
  }
  while (step) {
    ++it;
    --step;
  }
  return it;
}

template <class Iterator>
Iterator Next(Iterator it, typename std::iterator_traits<Iterator>::difference_type step = 1) {
  if constexpr (std::is_same_v<std::random_access_iterator_tag,
                               typename std::iterator_traits<Iterator>::iterator_category>) {
    return it += step;
  }
  if constexpr (std::is_same_v<std::bidirectional_iterator_tag,
                               typename std::iterator_traits<Iterator>::iterator_category>) {
    if (step < 0) {
      while (step) {
        --it;
        ++step;
      }
      return it;
    }
  }
  while (step) {
    ++it;
    --step;
  }
  return it;
}

template <class Iterator>
Iterator Prev(Iterator it, typename std::iterator_traits<Iterator>::difference_type step = 1) {
  if constexpr (std::is_same_v<std::random_access_iterator_tag,
                               typename std::iterator_traits<Iterator>::iterator_category>) {
    return it -= step;
  }
  if (step < 0) {
    while (step) {
      ++it;
      ++step;
    }
    return it;
  }
  while (step) {
    --it;
    --step;
  }
  return it;
}

template <class Iterator>
typename std::iterator_traits<Iterator>::difference_type Distance(Iterator begin, Iterator end) {
  if constexpr (std::is_same_v<std::random_access_iterator_tag,
                               typename std::iterator_traits<Iterator>::iterator_category>) {
    return end - begin;
  }
  typename std::iterator_traits<Iterator>::difference_type n = 0;
  while (begin != end) {
    ++begin;
    ++n;
  }
  return n;
}

#endif