#ifndef REVERSED_H
#define REVERSED_H
#define REVERSE_REVERSED_IMPLEMENTED

template <class Container>
class Reversed {
 private:
  Container& container_;

 public:
  explicit Reversed(Container& container) : container_(container) {
  }

  using iterator = Container::reverse_iterator;                 // NOLINT
  using const_iterator = Container::const_reverse_iterator;     // NOLINT
  using reverse_iterator = Container::iterator;                 // NOLINT
  using const_reverse_iterator = Container::const_iterator;     // NOLINT

  iterator begin() const {  // NOLINT
    return container_.rbegin();
  }

  iterator end() const {  // NOLINT
    return container_.rend();
  }

  reverse_iterator rbegin() const {  // NOLINT
    return container_.begin();
  }

  reverse_iterator rend() const {  // NOLINT
    return container_.end();
  }
};

template <class Container>
class Reversed<const Container> {
 private:
  const Container& container_;

 public:
  explicit Reversed(const Container& container) : container_(container) {
  }

  using iterator = Container::reverse_iterator;                 // NOLINT
  using const_iterator = Container::const_reverse_iterator;     // NOLINT
  using reverse_iterator = Container::const_iterator;           // NOLINT
  using const_reverse_iterator = Container::const_iterator;     // NOLINT

  const_iterator begin() const {  // NOLINT
    return container_.crbegin();
  }

  const_iterator end() const {  // NOLINT
    return container_.crend();
  }

  const_reverse_iterator rbegin() const {  // NOLINT
    return container_.cbegin();
  }

  const_reverse_iterator rend() const {  // NOLINT
    return container_.cend();
  }
};

#endif