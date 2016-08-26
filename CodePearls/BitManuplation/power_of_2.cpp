#include<type_traits>

template<typename T>
inline bool is_power_of_two(T x)
{
  return (x & (x-1));
}
