#include <mruby.h>

#include "mrb_gl2.h"
#include "mrb_gl2ext.h"

void
mrb_mruby_gles_gem_init(mrb_state* mrb)
{
  mrb_mruby_gles_gem_gl2_init(mrb);
#ifdef MRBGEM_GLES_ENABLE_EXT
  mrb_mruby_gles_gem_gl2ext_init(mrb);
#endif
}
