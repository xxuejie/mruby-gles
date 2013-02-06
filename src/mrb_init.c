#include <mruby.h>

#include "mrb_gl2.h"
#include "mrb_gl2ext.h"
#include "mrb_glut.h"

void
mrb_mruby_gles_gem_init(mrb_state* mrb)
{
  mrb_mruby_gles_gem_gl2_init(mrb);

#ifdef MRBGEM_GLES_ENABLE_GLUT
  mrb_mruby_gles_gem_glut_init(mrb);
#endif

#ifdef MRBGEM_GLES_ENABLE_EXT
  mrb_mruby_gles_gem_gl2ext_init(mrb);
#endif
}

void mrb_mruby_gles_gem_final(mrb_state* mrb)
{
}
