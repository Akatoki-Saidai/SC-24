#ifndef SC24_FM_FM_HPP_
#define SC24_FM_FM_HPP_

#include <cmath>

enum class Phase {
  Wait,
  Fall,
  Goal,
};

template <typename T> double abs_sum(T vec3) {
  double sum = 0;
  for (double n : vec3) {
    sum += std::abs(n);
  }
  return sum;
}

#endif // SC24_FM_FM_HPP_