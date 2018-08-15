#include <iostream>
#include <map>


// #define OUTPUT_TO_CONSOLE 1

#define CONTAINER_SIZE 10

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
