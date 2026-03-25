#ifndef PE_VECTOR_HPP
#DEFINE PE_VECTOR_HPP
namespace knk
{
  template< class T >
  class Vector {
   public:
    Vector();
    ~Vector();

   private:
    T* data;
    size_t size, capacity;
  };
}

#endif
