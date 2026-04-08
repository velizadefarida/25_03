#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>

namespace knk {
  template< class T >
  class Vector {
   public:
    ~Vector();
    Vector();
    Vector(const Vector< T >& rhs) = delete;
    Vector(size_t size, const T& value);
    Vector< T >& operator=(const Vector< T >& rhs);
    explicit Vector(size_t size);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    void pushBack(const T&);
    void popBack();

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);

   private:
    T* data_;
    size_t size_, capacity_;
  };
}
template< class T >
T& knk::Vector< T >::at(size_t id)
{
  if (id < getSize()) {
    return data_[id]
  }
  throw std::logic_error("id < size");
}

template< class T >
knk::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{
  for (size_t i = 0; i < size; ++i) {
    try {
      data_[i] = value;
    } catch (...) {
      delete [] data_;
      throw;
    }
    ++size_;
  }
}

template< class T >
size_t knk::Vector< T >::getSize() const noexcept {
  return size_;
}

template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

template< class T >
knk::Vector< T >::~Vector() {
  delete [] data_;
}

template< class T >
knk::Vector< T >::Vector() :
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

#endif
