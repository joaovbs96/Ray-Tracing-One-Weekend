#ifndef HITABLEH
#define HITABLEH

#include "../ray.h"
#include "aabb.h"

class material;

void get_sphere_uv(const vec3& p, float& u, float& v) {
  float phi = atan2(p.z(), p.x());
  float theta = asin(p.y());
  u = 1 - (phi + PI_F) / (2.0f * PI_F);
  v = (theta + PI_F / 2.0f) / PI_F;
}

struct hit_record {
  float t;
  float u;
  float v;
  vec3 p;
  vec3 normal;
  material* mat_ptr;
};

class hitable {
 public:
  virtual bool hit(const Ray&, float t_min, float t_max,
                   hit_record& rec) const = 0;
  virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
  virtual float pdf_value(const vec3& o, const vec3& v) const { return 0.0; }
  virtual vec3 random(const vec3& o) const { return vec3(1, 0, 0); }
};

#endif  // !HITABLEH
