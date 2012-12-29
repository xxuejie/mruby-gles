#include <mruby.h>

#ifdef EMSCRIPTEN
#include <GLES2/gl2.h>
#endif

static struct RClass *mod_gl2;

void
mrb_mruby_gles_gem_init(mrb_state* mrb)
{
  mod_gl2 = mrb_define_module(mrb, "GL2");

  /* constants */
  mrb_define_const(mrb, mod_gl2, "GL_ES_VERSION_2_0", mrb_fixnum_value(GL_ES_VERSION_2_0));

  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_BUFFER_BIT", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BUFFER_BIT", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT));
  mrb_define_const(mrb, mod_gl2, "GL_COLOR_BUFFER_BIT", mrb_fixnum_value(GL_COLOR_BUFFER_BIT));

  mrb_define_const(mrb, mod_gl2, "GL_FALSE", mrb_fixnum_value(GL_FALSE));
  mrb_define_const(mrb, mod_gl2, "GL_TRUE", mrb_fixnum_value(GL_TRUE));

  mrb_define_const(mrb, mod_gl2, "GL_POINTS", mrb_fixnum_value(GL_POINTS));
  mrb_define_const(mrb, mod_gl2, "GL_LINES", mrb_fixnum_value(GL_LINES));
  mrb_define_const(mrb, mod_gl2, "GL_LINE_LOOP", mrb_fixnum_value(GL_LINE_LOOP));
  mrb_define_const(mrb, mod_gl2, "GL_LINE_STRIP", mrb_fixnum_value(GL_LINE_STRIP));
}
