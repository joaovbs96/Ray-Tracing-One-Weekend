#pragma once

#include "../math/float3.hpp"

class Ray {
 public:
  Ray(const float3& o, const float3& d)
      : origin_(o), direction_(normalize(d)) {}

  const float3& origin() const { return origin_; }
  const float3& direction() const { return direction_; }

  float3 point_at(const float t) const { return origin_ + t * direction_; }

 private:
  float3 origin_;
  float3 direction_;
};