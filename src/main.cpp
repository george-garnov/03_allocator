#include <iostream>
#include <map>
#include "allocator.h"
#include "container.h"

// #define OUTPUT_TO_CONSOLE 1

#define CONTAINER_SIZE 10

constexpr int fact(int n)
{
  return ((n==0) ? 1 : n*fact(n-1));
}

int main(int, char *[])
{
    // std::map container, std::allocator 
    auto m1 = std::map<int, int>{};
    for (int i = 0; i < 10; i++)
    {
      m1[i] = fact(i);
    }
    
    // for (auto it = m1.begin(); it != m1.end(); ++it)
    // {
    //   std::cout << it->first << " " << it->second << std::endl;
    // }
    
    // std::map container, custom allocator 
    auto m2 = std::map<int, int, std::less<int>, allocator<std::pair<const int, int>, CONTAINER_SIZE>>{};
    for (int i = 0; i < CONTAINER_SIZE; i++)
    {
      m2[i] = fact(i);
    }
    
    for (auto it = m2.begin(); it != m2.end(); ++it)
    {
      std::cout << it->first << " " << it->second << std::endl;
    }
      
    //-----------------------------------------------------------
    // custom container, std::allocator
    auto c1 = container<int>{};
    for (int i = 0; i < CONTAINER_SIZE; i++)
    {
      c1.push_back(i);
    }
    
    // for (const auto &i: c1)
    //   std::cout << i << std::endl;
    
    // custom container, custom allocator  
    auto c2 = container<int, allocator<const int, CONTAINER_SIZE>>{};
    for (int i = 0; i < CONTAINER_SIZE; i++)
    {
      c2.push_back(i);
    }
    
    for (const auto &i: c2)
    {
      std::cout << i << std::endl;
    }

    return 0;
}
