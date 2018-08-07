#ifndef __PRETTY_FUNCTION__
///#include "pretty.h"
#endif

#include <iostream>
#include <deque>
#include <map>

// #define USE_PRETTY 1

#define CONTAINER_SIZE 10

template<typename T, size_t N>
struct map_allocator {
    
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = map_allocator<U, N>;
    };

    map_allocator():memptr(N)
    {
      for(auto i=0; i<N; i++) memptr[i] = memory+i;
    }
    ~map_allocator() = default;

    template<typename U> 
    map_allocator(const map_allocator<U, N>&) {
      
    }

    T *allocate(std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        if (memptr.size() == 0) throw std::bad_alloc();
        auto p = memptr.back();
        
        std::cout << "memptr: " << p-memory << std::endl;
        
        memptr.pop_back();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        std::cout << "memptr: " << p-memory << std::endl;
        memptr.push_back(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifndef USE_PRETTY
        std::cout << "construct" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) {
#ifndef USE_PRETTY
        std::cout << "destroy" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        p->~T();
    }
    
private:
  T memory[N];
  std::deque<T*> memptr;
};

constexpr int fact(int n)
{
  return ((n==0) ? 1 : n*fact(n-1));
}


int main(int, char *[])
{
    auto m = std::map<int, int, std::less<int>, map_allocator<std::pair<const int, int>, CONTAINER_SIZE>>{};
    for (int i = 0; i < CONTAINER_SIZE; i++)
    {
      m[i] = fact(i);
      std::cout << "Key: " << i << "; Value: " << m[i] << std::endl;
    }

    return 0;
}
