#pragma once

template<typename T>
struct ContainerCell {
  ContainerCell() = default;
  explicit ContainerCell(const T &val) : data{val}, next{nullptr} {}

  T data;
  ContainerCell *next;
};

template<typename T, typename Alloc = std::allocator<T> >
class container {
  using cell_t = ContainerCell<T>;

  using alloc_t = typename Alloc::template rebind<cell_t>::other;
  alloc_t alloc;
  
  cell_t *first = nullptr;
  cell_t *last  = nullptr;  
    
public:

  struct iterator : std::iterator<std::forward_iterator_tag, T>
  {
    explicit iterator(cell_t *cell = nullptr) : ptr(cell) {}
    iterator() = delete;

    iterator &operator++()
    {
      if (ptr != nullptr)
      {
        ptr = ptr->next;
      }
      return *this;
    }

    T &operator*()
    {
      return ptr->data;
    }

    bool operator==(iterator &other)
    {
      return ptr == other.ptr;
    }

    bool operator!=(iterator &other)
    {
      return !(*this == other);
    }

  private:
    cell_t *ptr;
  };
    
  container() = default;

  ~container()
  {
    for(auto i=first;i;)
    {
      auto p = i;
      i = i->next;
      alloc.destroy(p);
      alloc.deallocate(p, 1);
    }
  }

  void push_back(const T &value)
  {
    cell_t *p = alloc.allocate(1);
    alloc.construct(p, value);

    if (last)
    {
      last->next = p;
    }
    else
    {
      first = p;
    }
    last = p;
  }

  iterator begin() {return iterator(first);}

  iterator end()   {return iterator(nullptr);}

};
