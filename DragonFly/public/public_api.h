#ifndef DRAGONFLY_PUBLIC_HEADER
#define DRAGONFLY_PUBLIC_HEADER

#include "public_core.h"
#include <cstddef>

BEGIN_EXTERN_C

typedef struct drawable_allocator_t drawable_allocator_t;
typedef struct drawable_base_op_t drawable_base_op_t;
typedef struct drawable_base_t drawable_base_t;
typedef struct triangle_t triangle_t;
typedef struct rectangle_t rectangle_t;
typedef struct circle_t circle_t;

typedef struct drawable_allocator_t
{
  typedef void *(DRAGONFLY_API_CALL *allocate_t)(size_t size) NOEXCEPT;
  typedef void (DRAGONFLY_API_CALL *deallocate_t)(void *ptr) NOEXCEPT;
  const allocate_t f_allocate;
  const deallocate_t f_deallocate;
} drawable_allocator_t;

typedef struct drawable_base_op_t
{
  typedef void(DRAGONFLY_API_CALL *draw_t)(void) NOEXCEPT;
  const draw_t f_draw;
} drawable_base_op_t;

typedef struct drawable_base_t
{
  const drawable_allocator_t *m_allocator;
  const drawable_base_op_t *m_vtable;
} drawable_base_t;

typedef struct triangle_t
{
  drawable_base_t m_base;
  double m_verts[9];
} triangle_t;

typedef struct rectangle_t
{
  drawable_base_t m_base;
  double m_verts[12];
} rectangle_t;

typedef struct circle_t
{
  drawable_base_t m_base;
  double m_org[4];
} circle_t;

DRAGONFLY_EXPORT_SYMBOL drawable_base_t * DRAGONFLY_API_CALL create_triangle(drawable_allocator_t *allocator = NULL) NOEXCEPT;
DRAGONFLY_EXPORT_SYMBOL drawable_base_t * DRAGONFLY_API_CALL create_rectangle(drawable_allocator_t *allocator = NULL) NOEXCEPT;
DRAGONFLY_EXPORT_SYMBOL drawable_base_t * DRAGONFLY_API_CALL create_circle(drawable_allocator_t *allocator = NULL) NOEXCEPT;
DRAGONFLY_EXPORT_SYMBOL void DRAGONFLY_API_CALL destroy_triangle(drawable_base_t *triangle) NOEXCEPT;
DRAGONFLY_EXPORT_SYMBOL void DRAGONFLY_API_CALL destroy_rectangle(drawable_base_t *rectangle) NOEXCEPT;
DRAGONFLY_EXPORT_SYMBOL void DRAGONFLY_API_CALL destroy_circle(drawable_base_t *circle) NOEXCEPT;

END_EXTERN_C

#endif

