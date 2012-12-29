#include <mruby.h>

#include "mrb_gl2.h"
#include "mrb_gl2ext.h"

void
mrb_mruby_gles_gem_init(mrb_state* mrb)
{
  mrb_mruby_gles_gem_gl2_init(mrb);
  mrb_mruby_gles_gem_gl2ext_init(mrb);
}
