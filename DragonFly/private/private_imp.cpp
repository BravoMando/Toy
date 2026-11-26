import public_api;
import std;

#include "public_api.h"

BEGIN_EXTERN_C

static void DRAGONFLY_API_CALL draw_triangle() NOEXCEPT
{
  std::println("draw_triangle");
}

static void DRAGONFLY_API_CALL draw_rectangle() NOEXCEPT
{
  std::println("draw_rectangle");
}

static void DRAGONFLY_API_CALL draw_circle() NOEXCEPT
{
  std::println("draw_circle");
}

const drawable_base_op_t g_triangle_op{.f_draw = draw_triangle};
const drawable_base_op_t g_rectangle_op{.f_draw = draw_rectangle};
const drawable_base_op_t g_circle_op{.f_draw = draw_circle};

drawable_base_t * DRAGONFLY_API_CALL create_triangle(drawable_allocator_t *allocator) NOEXCEPT
{
  std::println("create_triangle");
  triangle_t *tri = nullptr;
  if (allocator)
  {
    tri = reinterpret_cast<triangle_t *>(allocator->f_allocate(sizeof(triangle_t)));
  }
  else
  {
    tri = new triangle_t();
  }
  tri->m_base.m_allocator = allocator;
  tri->m_base.m_vtable = &g_triangle_op;
  return &tri->m_base;
}

drawable_base_t * DRAGONFLY_API_CALL create_rectangle(drawable_allocator_t *allocator) NOEXCEPT
{
  std::println("create_rectangle");
  rectangle_t *rec = nullptr;
  if (allocator)
  {
    rec = reinterpret_cast<rectangle_t *>(allocator->f_allocate(sizeof(rectangle_t)));
  }
  else
  {
    rec = new rectangle_t();
  }
  rec->m_base.m_allocator = allocator;
  rec->m_base.m_vtable = &g_rectangle_op;
  return &rec->m_base;
}

drawable_base_t * DRAGONFLY_API_CALL create_circle(drawable_allocator_t *allocator) NOEXCEPT
{
  std::println("create_circle");
  circle_t *cir = nullptr;
  if (allocator)
  {
    cir = reinterpret_cast<circle_t *>(allocator->f_allocate(sizeof(circle_t)));
  }
  else
  {
    cir = new circle_t();
  }
  cir->m_base.m_allocator = allocator;
  cir->m_base.m_vtable = &g_circle_op;
  return &cir->m_base;
}

void DRAGONFLY_API_CALL destroy_triangle(drawable_base_t *triangle) NOEXCEPT
{
  std::println("destroy_triangle");
  triangle_t *tri = CONTAINER_OF(triangle_t, triangle, m_base);
  if (tri->m_base.m_allocator)
  {
    tri->m_base.m_allocator->f_deallocate(tri);
  }
  else
  {
    delete tri;
  }
}

void DRAGONFLY_API_CALL destroy_rectangle(drawable_base_t *rectangle) NOEXCEPT
{
  std::println("destroy_rectangle");
  rectangle_t *rec = CONTAINER_OF(rectangle_t, rectangle, m_base);
  if (rec->m_base.m_allocator)
  {
    rec->m_base.m_allocator->f_deallocate(rec);
  }
  else
  {
    delete rec;
  }
}

void DRAGONFLY_API_CALL destroy_circle(drawable_base_t *circle) NOEXCEPT
{
  std::println("destroy_circle");
  circle_t *cir = CONTAINER_OF(circle_t, circle, m_base);
  if (cir->m_base.m_allocator)
  {
    cir->m_base.m_allocator->f_deallocate(cir);
  }
  else
  {
    delete cir;
  }
}

END_EXTERN_C

