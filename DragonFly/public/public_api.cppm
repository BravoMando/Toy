module;

#include "public_api.h"

export module public_api;

export {

  using ::drawable_allocator_t;
  using ::drawable_base_op_t;
  using ::drawable_base_t;
  using ::triangle_t;
  using ::rectangle_t;
  using ::circle_t;

  using ::create_triangle;
  using ::create_rectangle;
  using ::create_circle;
  using ::destroy_triangle;
  using ::destroy_rectangle;
  using ::destroy_circle;
}
