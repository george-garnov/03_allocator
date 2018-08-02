#ifndef __PRETTY_FUNCTION__
///#include "pretty.h"
#endif

#include <iostream>
#include <vector>
#include <deque>
#include <map>

// #define USE_PRETTY 1

template<typename T>
struct map_allocator {
    static const std::size_t N = 10;
    
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = map_allocator<U>;
    };

    map_allocator():ptr(N)
    {
      for(auto i=0; i<N; i++) ptr[i] = memory+i;
    }
    ~map_allocator() = default;

    template<typename U> 
    map_allocator(const map_allocator<U>&) {
      
    }

    T *allocate(std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "allocate: [n = " << n << "]" << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
#ifndef USE_PRETTY
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#else
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
#endif
        std::free(p);
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
  std::deque<T*> ptr;//(std::size_t n = N);
};

int main(int, char *[]) {

    auto m = std::map<int, int, std::less<int>, map_allocator<std::pair<const int, int>>>{};
    for (int i = 0; i < 5; ++i) {
      m[i] = i;
      std::cout << m.size() << " : " << sizeof(m) << std::endl;
    }
    

    return 0;
}
