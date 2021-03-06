#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list : public hitable {
 public:
  hitable_list() {}

  hitable_list(hitable** l, int n) {
    list = l;
    list_size = n;
  }

  virtual bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
  virtual bool bounding_box(float t0, float t1, aabb& box) const;
  virtual float pdf_value(const vec3& o, const vec3& v) const;
  virtual vec3 random(const vec3& o) const;

  hitable** list;
  int list_size;
};

bool hitable_list::hit(const Ray& r, float t_min, float t_max,
                       hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  float closest_so_far = t_max;

  // Iterates list of hitables to check if Ray intersects/hits anything
  // If so, returns true. Otherwise, false.
  for (int i = 0; i < list_size; i++) {
    if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}

bool hitable_list::bounding_box(float t0, float t1, aabb& box) const {
  if (list_size < 1) return false;

  aabb temp_box;
  bool first_true = list[0]->bounding_box(t0, t1, temp_box);

  if (!first_true)
    return false;
  else
    box = temp_box;

  for (int i = 1; i < list_size; i++) {
    if (list[i]->bounding_box(t0, t1, temp_box))
      box = surrounding_box(box, temp_box);
    else
      return false;
  }

  return true;
}

float hitable_list::pdf_value(const vec3& o, const vec3& v) const {
  float weight = 1.0f / list_size;
  float sum = 0.0f;

  for (int i = 0; i < list_size; i++) sum += weight * list[i]->pdf_value(o, v);

  return sum;
}

vec3 hitable_list::random(const vec3& o) const {
  int index = int(RFG() * list_size);
  return list[index]->random(o);
}

#endif  // !HITABLELISTH
