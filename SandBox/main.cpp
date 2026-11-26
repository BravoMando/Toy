#include "public_core.h"

import public_api;
import std;

static void * DRAGONFLY_API_CALL allocate(size_t size) NOEXCEPT
{
  return reinterpret_cast<void*>(new std::byte[size]);
}

static void DRAGONFLY_API_CALL deallocate(void *ptr) NOEXCEPT
{
  delete[] reinterpret_cast<std::byte *>(ptr);
}

drawable_allocator_t g_allocator{.f_allocate = allocate,
  .f_deallocate = deallocate};

int main()
{
  drawable_base_t *tri = create_triangle(&g_allocator);
  drawable_base_t *rec = create_rectangle(&g_allocator);
  drawable_base_t *cir = create_circle(&g_allocator);

  tri->m_vtable->f_draw();
  rec->m_vtable->f_draw();
  cir->m_vtable->f_draw();

  destroy_triangle(tri);
  destroy_rectangle(rec);
  destroy_circle(cir);

  return 0;
}

