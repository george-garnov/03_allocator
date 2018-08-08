#include <iostream>
#include <map>


// #define OUTPUT_TO_CONSOLE 1

#define CONTAINER_SIZE 10

template <typename T, size_t N>
class Stack{
    size_t cnt;
    T mem[N];
public:
   Stack() {cnt=0;}
   ~Stack() = default;
   void push(T val){if(cnt<10) mem[cnt++] = val;}
   T pop(){return cnt ? mem[--cnt] : 0;}
};

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

    map_allocator()
    {
       for(auto i=0;i<N;i++) ptr.push(memory+i);
    }
    ~map_allocator() = default;

    template<typename U> 
    map_allocator(const map_allocator<U, N>&) {

    }

    T *allocate(std::size_t n) {
        auto p = ptr.pop();
        if (!p) throw std::bad_alloc();
        
#ifdef OUTPUT_TO_CONSOLE
        std::cout << "allocate: [n = " << n << "]" << std::endl;
        std::cout << "memptr: " << p-memory << std::endl;
#endif      
        
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
#ifdef OUTPUT_TO_CONSOLE
        std::cout << "deallocate: [n  = " << n << "] " << std::endl;
        std::cout << "memptr: " << p-memory << std::endl;
#endif
        ptr.push(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifdef OUTPUT_TO_CONSOLE
        std::cout << "construct" << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) {
#ifdef OUTPUT_TO_CONSOLE
        std::cout << "destroy" << std::endl;
#endif
        p->~T();
    }
    
private:
  T memory[N];
  Stack<T*,N> ptr;
};

constexpr int fact(int n)
{
  return ((n==0) ? 1 : n*fact(n-1));
}


int main(int, char *[])
{
    auto m1 = std::map<int, int>{};
    for (int i = 0; i < 10; i++)
    {
      m1[i] = fact(i);
    }
    
    auto m2 = std::map<int, int, std::less<int>, map_allocator<std::pair<const int, int>, CONTAINER_SIZE>>{};
    for (int i = 0; i < CONTAINER_SIZE; i++)
    {
      m2[i] = fact(i);
      std::cout << "Key: " << i << "; Value: " << m2[i] << std::endl;
    }

    return 0;
}
