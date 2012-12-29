#include <mruby.h>

#ifdef EMSCRIPTEN
#include <GLES2/gl2.h>
#endif

static struct RClass *mod_gl2;

void
mrb_mruby_gles_gem_gl2_init(mrb_state* mrb)
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
  mrb_define_const(mrb, mod_gl2, "GL_TRIANGLES", mrb_fixnum_value(GL_TRIANGLES));
  mrb_define_const(mrb, mod_gl2, "GL_TRIANGLE_STRIP", mrb_fixnum_value(GL_TRIANGLE_STRIP));
  mrb_define_const(mrb, mod_gl2, "GL_TRIANGLE_FAN", mrb_fixnum_value(GL_TRIANGLE_FAN));

  mrb_define_const(mrb, mod_gl2, "GL_ZERO", mrb_fixnum_value(GL_ZERO));
  mrb_define_const(mrb, mod_gl2, "GL_ONE", mrb_fixnum_value(GL_ONE));
  mrb_define_const(mrb, mod_gl2, "GL_SRC_COLOR", mrb_fixnum_value(GL_SRC_COLOR));
  mrb_define_const(mrb, mod_gl2, "GL_ONE_MINUS_SRC_COLOR", mrb_fixnum_value(GL_ONE_MINUS_SRC_COLOR));
  mrb_define_const(mrb, mod_gl2, "GL_SRC_ALPHA", mrb_fixnum_value(GL_SRC_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_ONE_MINUS_SRC_ALPHA", mrb_fixnum_value(GL_ONE_MINUS_SRC_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_DST_ALPHA", mrb_fixnum_value(GL_DST_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_ONE_MINUS_DST_ALPHA", mrb_fixnum_value(GL_ONE_MINUS_DST_ALPHA));

  mrb_define_const(mrb, mod_gl2, "GL_DST_COLOR", mrb_fixnum_value(GL_DST_COLOR));
  mrb_define_const(mrb, mod_gl2, "GL_ONE_MINUS_DST_COLOR", mrb_fixnum_value(GL_ONE_MINUS_DST_COLOR));
  mrb_define_const(mrb, mod_gl2, "GL_SRC_ALPHA_SATURATE", mrb_fixnum_value(GL_SRC_ALPHA_SATURATE));

  mrb_define_const(mrb, mod_gl2, "GL_FUNC_ADD", mrb_fixnum_value(GL_FUNC_ADD));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND_EQUATION", mrb_fixnum_value(GL_BLEND_EQUATION));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND_EQUATION_RGB", mrb_fixnum_value(GL_BLEND_EQUATION_RGB));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND_EQUATION_ALPHA", mrb_fixnum_value(GL_BLEND_EQUATION_ALPHA));

  mrb_define_const(mrb, mod_gl2, "GL_FUNC_SUBTRACT", mrb_fixnum_value(GL_FUNC_SUBTRACT));
  mrb_define_const(mrb, mod_gl2, "GL_FUNC_REVERSE_SUBTRACT", mrb_fixnum_value(GL_FUNC_REVERSE_SUBTRACT));

  mrb_define_const(mrb, mod_gl2, "GL_BLEND_DST_RGB", mrb_fixnum_value(GL_BLEND_DST_RGB));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND_SRC_RGB", mrb_fixnum_value(GL_BLEND_SRC_RGB));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND_DST_ALPHA", mrb_fixnum_value(GL_BLEND_DST_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND_SRC_ALPHA", mrb_fixnum_value(GL_BLEND_SRC_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_CONSTANT_COLOR", mrb_fixnum_value(GL_CONSTANT_COLOR));
  mrb_define_const(mrb, mod_gl2, "GL_ONE_MINUS_CONSTANT_COLOR", mrb_fixnum_value(GL_ONE_MINUS_CONSTANT_COLOR));
  mrb_define_const(mrb, mod_gl2, "GL_CONSTANT_ALPHA", mrb_fixnum_value(GL_CONSTANT_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_ONE_MINUS_CONSTANT_ALPHA", mrb_fixnum_value(GL_ONE_MINUS_CONSTANT_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND_COLOR", mrb_fixnum_value(GL_BLEND_COLOR));

  mrb_define_const(mrb, mod_gl2, "GL_ARRAY_BUFFER", mrb_fixnum_value(GL_ARRAY_BUFFER));
  mrb_define_const(mrb, mod_gl2, "GL_ELEMENT_ARRAY_BUFFER", mrb_fixnum_value(GL_ELEMENT_ARRAY_BUFFER));
  mrb_define_const(mrb, mod_gl2, "GL_ARRAY_BUFFER_BINDING", mrb_fixnum_value(GL_ARRAY_BUFFER_BINDING));
  mrb_define_const(mrb, mod_gl2, "GL_ELEMENT_ARRAY_BUFFER_BINDING", mrb_fixnum_value(GL_ELEMENT_ARRAY_BUFFER_BINDING));

  mrb_define_const(mrb, mod_gl2, "GL_STREAM_DRAW", mrb_fixnum_value(GL_STREAM_DRAW));
  mrb_define_const(mrb, mod_gl2, "GL_STATIC_DRAW", mrb_fixnum_value(GL_STATIC_DRAW));
  mrb_define_const(mrb, mod_gl2, "GL_DYNAMIC_DRAW", mrb_fixnum_value(GL_DYNAMIC_DRAW));

  mrb_define_const(mrb, mod_gl2, "GL_BUFFER_SIZE", mrb_fixnum_value(GL_BUFFER_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_BUFFER_USAGE", mrb_fixnum_value(GL_BUFFER_USAGE));

  mrb_define_const(mrb, mod_gl2, "GL_CURRENT_VERTEX_ATTRIB", mrb_fixnum_value(GL_CURRENT_VERTEX_ATTRIB));

  mrb_define_const(mrb, mod_gl2, "GL_FRONT", mrb_fixnum_value(GL_FRONT));
  mrb_define_const(mrb, mod_gl2, "GL_BACK", mrb_fixnum_value(GL_BACK));
  mrb_define_const(mrb, mod_gl2, "GL_FRONT_AND_BACK", mrb_fixnum_value(GL_FRONT_AND_BACK));

  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_2D", mrb_fixnum_value(GL_TEXTURE_2D));
  mrb_define_const(mrb, mod_gl2, "GL_CULL_FACE", mrb_fixnum_value(GL_CULL_FACE));
  mrb_define_const(mrb, mod_gl2, "GL_BLEND", mrb_fixnum_value(GL_BLEND));
  mrb_define_const(mrb, mod_gl2, "GL_DITHER", mrb_fixnum_value(GL_DITHER));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_TEST", mrb_fixnum_value(GL_STENCIL_TEST));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_TEST", mrb_fixnum_value(GL_DEPTH_TEST));
  mrb_define_const(mrb, mod_gl2, "GL_SCISSOR_TEST", mrb_fixnum_value(GL_SCISSOR_TEST));
  mrb_define_const(mrb, mod_gl2, "GL_POLYGON_OFFSET_FILL", mrb_fixnum_value(GL_POLYGON_OFFSET_FILL));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLE_ALPHA_TO_COVERAGE", mrb_fixnum_value(GL_SAMPLE_ALPHA_TO_COVERAGE));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLE_COVERAGE", mrb_fixnum_value(GL_SAMPLE_COVERAGE));

  mrb_define_const(mrb, mod_gl2, "GL_NO_ERROR", mrb_fixnum_value(GL_NO_ERROR));
  mrb_define_const(mrb, mod_gl2, "GL_INVALID_ENUM", mrb_fixnum_value(GL_INVALID_ENUM));
  mrb_define_const(mrb, mod_gl2, "GL_INVALID_VALUE", mrb_fixnum_value(GL_INVALID_VALUE));
  mrb_define_const(mrb, mod_gl2, "GL_INVALID_OPERATION", mrb_fixnum_value(GL_INVALID_OPERATION));
  mrb_define_const(mrb, mod_gl2, "GL_OUT_OF_MEMORY", mrb_fixnum_value(GL_OUT_OF_MEMORY));

  mrb_define_const(mrb, mod_gl2, "GL_CW", mrb_fixnum_value(GL_CW));
  mrb_define_const(mrb, mod_gl2, "GL_CCW", mrb_fixnum_value(GL_CCW));

  mrb_define_const(mrb, mod_gl2, "GL_LINE_WIDTH", mrb_fixnum_value(GL_LINE_WIDTH));
  mrb_define_const(mrb, mod_gl2, "GL_ALIASED_POINT_SIZE_RANGE", mrb_fixnum_value(GL_ALIASED_POINT_SIZE_RANGE));
  mrb_define_const(mrb, mod_gl2, "GL_ALIASED_LINE_WIDTH_RANGE", mrb_fixnum_value(GL_ALIASED_LINE_WIDTH_RANGE));
  mrb_define_const(mrb, mod_gl2, "GL_CULL_FACE_MODE", mrb_fixnum_value(GL_CULL_FACE_MODE));
  mrb_define_const(mrb, mod_gl2, "GL_FRONT_FACE", mrb_fixnum_value(GL_FRONT_FACE));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_RANGE", mrb_fixnum_value(GL_DEPTH_RANGE));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_WRITEMASK", mrb_fixnum_value(GL_DEPTH_WRITEMASK));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_CLEAR_VALUE", mrb_fixnum_value(GL_DEPTH_CLEAR_VALUE));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_FUNC", mrb_fixnum_value(GL_DEPTH_FUNC));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_CLEAR_VALUE", mrb_fixnum_value(GL_STENCIL_CLEAR_VALUE));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_FUNC", mrb_fixnum_value(GL_STENCIL_FUNC));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_FAIL", mrb_fixnum_value(GL_STENCIL_FAIL));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_PASS_DEPTH_FAIL", mrb_fixnum_value(GL_STENCIL_PASS_DEPTH_FAIL));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_PASS_DEPTH_PASS", mrb_fixnum_value(GL_STENCIL_PASS_DEPTH_PASS));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_REF", mrb_fixnum_value(GL_STENCIL_REF));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_VALUE_MASK", mrb_fixnum_value(GL_STENCIL_VALUE_MASK));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_WRITEMASK", mrb_fixnum_value(GL_STENCIL_WRITEMASK));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BACK_FUNC", mrb_fixnum_value(GL_STENCIL_BACK_FUNC));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BACK_FAIL", mrb_fixnum_value(GL_STENCIL_BACK_FAIL));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BACK_PASS_DEPTH_FAIL", mrb_fixnum_value(GL_STENCIL_BACK_PASS_DEPTH_FAIL));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BACK_PASS_DEPTH_PASS", mrb_fixnum_value(GL_STENCIL_BACK_PASS_DEPTH_PASS));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BACK_REF", mrb_fixnum_value(GL_STENCIL_BACK_REF));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BACK_VALUE_MASK", mrb_fixnum_value(GL_STENCIL_BACK_VALUE_MASK));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BACK_WRITEMASK", mrb_fixnum_value(GL_STENCIL_BACK_WRITEMASK));
  mrb_define_const(mrb, mod_gl2, "GL_VIEWPORT", mrb_fixnum_value(GL_VIEWPORT));
  mrb_define_const(mrb, mod_gl2, "GL_SCISSOR_BOX", mrb_fixnum_value(GL_SCISSOR_BOX));

  mrb_define_const(mrb, mod_gl2, "GL_COLOR_CLEAR_VALUE", mrb_fixnum_value(GL_COLOR_CLEAR_VALUE));
  mrb_define_const(mrb, mod_gl2, "GL_COLOR_WRITEMASK", mrb_fixnum_value(GL_COLOR_WRITEMASK));
  mrb_define_const(mrb, mod_gl2, "GL_UNPACK_ALIGNMENT", mrb_fixnum_value(GL_UNPACK_ALIGNMENT));
  mrb_define_const(mrb, mod_gl2, "GL_PACK_ALIGNMENT", mrb_fixnum_value(GL_PACK_ALIGNMENT));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_TEXTURE_SIZE", mrb_fixnum_value(GL_MAX_TEXTURE_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_VIEWPORT_DIMS", mrb_fixnum_value(GL_MAX_VIEWPORT_DIMS));
  mrb_define_const(mrb, mod_gl2, "GL_SUBPIXEL_BITS", mrb_fixnum_value(GL_SUBPIXEL_BITS));
  mrb_define_const(mrb, mod_gl2, "GL_RED_BITS", mrb_fixnum_value(GL_RED_BITS));
  mrb_define_const(mrb, mod_gl2, "GL_GREEN_BITS", mrb_fixnum_value(GL_GREEN_BITS));
  mrb_define_const(mrb, mod_gl2, "GL_BLUE_BITS", mrb_fixnum_value(GL_BLUE_BITS));
  mrb_define_const(mrb, mod_gl2, "GL_ALPHA_BITS", mrb_fixnum_value(GL_ALPHA_BITS));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_BITS", mrb_fixnum_value(GL_DEPTH_BITS));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_BITS", mrb_fixnum_value(GL_STENCIL_BITS));
  mrb_define_const(mrb, mod_gl2, "GL_POLYGON_OFFSET_UNITS", mrb_fixnum_value(GL_POLYGON_OFFSET_UNITS));

  mrb_define_const(mrb, mod_gl2, "GL_POLYGON_OFFSET_FACTOR", mrb_fixnum_value(GL_POLYGON_OFFSET_FACTOR));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_BINDING_2D", mrb_fixnum_value(GL_TEXTURE_BINDING_2D));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLE_BUFFERS", mrb_fixnum_value(GL_SAMPLE_BUFFERS));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLES", mrb_fixnum_value(GL_SAMPLES));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLE_COVERAGE_VALUE", mrb_fixnum_value(GL_SAMPLE_COVERAGE_VALUE));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLE_COVERAGE_INVERT", mrb_fixnum_value(GL_SAMPLE_COVERAGE_INVERT));

  mrb_define_const(mrb, mod_gl2, "GL_NUM_COMPRESSED_TEXTURE_FORMATS", mrb_fixnum_value(GL_NUM_COMPRESSED_TEXTURE_FORMATS));
  mrb_define_const(mrb, mod_gl2, "GL_COMPRESSED_TEXTURE_FORMATS", mrb_fixnum_value(GL_COMPRESSED_TEXTURE_FORMATS));

  mrb_define_const(mrb, mod_gl2, "GL_DONT_CARE", mrb_fixnum_value(GL_DONT_CARE));
  mrb_define_const(mrb, mod_gl2, "GL_FASTEST", mrb_fixnum_value(GL_FASTEST));
  mrb_define_const(mrb, mod_gl2, "GL_NICEST", mrb_fixnum_value(GL_NICEST));

  mrb_define_const(mrb, mod_gl2, "GL_GENERATE_MIPMAP_HINT", mrb_fixnum_value(GL_GENERATE_MIPMAP_HINT));

  mrb_define_const(mrb, mod_gl2, "GL_BYTE", mrb_fixnum_value(GL_BYTE));
  mrb_define_const(mrb, mod_gl2, "GL_UNSIGNED_BYTE", mrb_fixnum_value(GL_UNSIGNED_BYTE));
  mrb_define_const(mrb, mod_gl2, "GL_SHORT", mrb_fixnum_value(GL_SHORT));
  mrb_define_const(mrb, mod_gl2, "GL_UNSIGNED_SHORT", mrb_fixnum_value(GL_UNSIGNED_SHORT));
  mrb_define_const(mrb, mod_gl2, "GL_INT", mrb_fixnum_value(GL_INT));
  mrb_define_const(mrb, mod_gl2, "GL_UNSIGNED_INT", mrb_fixnum_value(GL_UNSIGNED_INT));
  mrb_define_const(mrb, mod_gl2, "GL_FLOAT", mrb_fixnum_value(GL_FLOAT));
  mrb_define_const(mrb, mod_gl2, "GL_FIXED", mrb_fixnum_value(GL_FIXED));

  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_COMPONENT", mrb_fixnum_value(GL_DEPTH_COMPONENT));
  mrb_define_const(mrb, mod_gl2, "GL_ALPHA", mrb_fixnum_value(GL_ALPHA));
  mrb_define_const(mrb, mod_gl2, "GL_RGB", mrb_fixnum_value(GL_RGB));
  mrb_define_const(mrb, mod_gl2, "GL_RGBA", mrb_fixnum_value(GL_RGBA));
  mrb_define_const(mrb, mod_gl2, "GL_LUMINANCE", mrb_fixnum_value(GL_LUMINANCE));
  mrb_define_const(mrb, mod_gl2, "GL_LUMINANCE_ALPHA", mrb_fixnum_value(GL_LUMINANCE_ALPHA));

  mrb_define_const(mrb, mod_gl2, "GL_UNSIGNED_SHORT_4_4_4_4", mrb_fixnum_value(GL_UNSIGNED_SHORT_4_4_4_4));
  mrb_define_const(mrb, mod_gl2, "GL_UNSIGNED_SHORT_5_5_5_1", mrb_fixnum_value(GL_UNSIGNED_SHORT_5_5_5_1));
  mrb_define_const(mrb, mod_gl2, "GL_UNSIGNED_SHORT_5_6_5", mrb_fixnum_value(GL_UNSIGNED_SHORT_5_6_5));

  mrb_define_const(mrb, mod_gl2, "GL_FRAGMENT_SHADER", mrb_fixnum_value(GL_FRAGMENT_SHADER));
  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_SHADER", mrb_fixnum_value(GL_VERTEX_SHADER));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_VERTEX_ATTRIBS", mrb_fixnum_value(GL_MAX_VERTEX_ATTRIBS));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_VERTEX_UNIFORM_VECTORS", mrb_fixnum_value(GL_MAX_VERTEX_UNIFORM_VECTORS));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_VARYING_VECTORS", mrb_fixnum_value(GL_MAX_VARYING_VECTORS));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", mrb_fixnum_value(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS", mrb_fixnum_value(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_TEXTURE_IMAGE_UNITS", mrb_fixnum_value(GL_MAX_TEXTURE_IMAGE_UNITS));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_FRAGMENT_UNIFORM_VECTORS", mrb_fixnum_value(GL_MAX_FRAGMENT_UNIFORM_VECTORS));
  mrb_define_const(mrb, mod_gl2, "GL_SHADER_TYPE", mrb_fixnum_value(GL_SHADER_TYPE));
  mrb_define_const(mrb, mod_gl2, "GL_DELETE_STATUS", mrb_fixnum_value(GL_DELETE_STATUS));
  mrb_define_const(mrb, mod_gl2, "GL_LINK_STATUS", mrb_fixnum_value(GL_LINK_STATUS));
  mrb_define_const(mrb, mod_gl2, "GL_VALIDATE_STATUS", mrb_fixnum_value(GL_VALIDATE_STATUS));
  mrb_define_const(mrb, mod_gl2, "GL_ATTACHED_SHADERS", mrb_fixnum_value(GL_ATTACHED_SHADERS));
  mrb_define_const(mrb, mod_gl2, "GL_ACTIVE_UNIFORMS", mrb_fixnum_value(GL_ACTIVE_UNIFORMS));
  mrb_define_const(mrb, mod_gl2, "GL_ACTIVE_UNIFORM_MAX_LENGTH", mrb_fixnum_value(GL_ACTIVE_UNIFORM_MAX_LENGTH));
  mrb_define_const(mrb, mod_gl2, "GL_ACTIVE_ATTRIBUTES", mrb_fixnum_value(GL_ACTIVE_ATTRIBUTES));
  mrb_define_const(mrb, mod_gl2, "GL_ACTIVE_ATTRIBUTE_MAX_LENGTH", mrb_fixnum_value(GL_ACTIVE_ATTRIBUTE_MAX_LENGTH));
  mrb_define_const(mrb, mod_gl2, "GL_SHADING_LANGUAGE_VERSION", mrb_fixnum_value(GL_SHADING_LANGUAGE_VERSION));
  mrb_define_const(mrb, mod_gl2, "GL_CURRENT_PROGRAM", mrb_fixnum_value(GL_CURRENT_PROGRAM));

  mrb_define_const(mrb, mod_gl2, "GL_NEVER", mrb_fixnum_value(GL_NEVER));
  mrb_define_const(mrb, mod_gl2, "GL_LESS", mrb_fixnum_value(GL_LESS));
  mrb_define_const(mrb, mod_gl2, "GL_EQUAL", mrb_fixnum_value(GL_EQUAL));
  mrb_define_const(mrb, mod_gl2, "GL_LEQUAL", mrb_fixnum_value(GL_LEQUAL));
  mrb_define_const(mrb, mod_gl2, "GL_GREATER", mrb_fixnum_value(GL_GREATER));
  mrb_define_const(mrb, mod_gl2, "GL_NOTEQUAL", mrb_fixnum_value(GL_NOTEQUAL));
  mrb_define_const(mrb, mod_gl2, "GL_GEQUAL", mrb_fixnum_value(GL_GEQUAL));
  mrb_define_const(mrb, mod_gl2, "GL_ALWAYS", mrb_fixnum_value(GL_ALWAYS));

  mrb_define_const(mrb, mod_gl2, "GL_KEEP", mrb_fixnum_value(GL_KEEP));
  mrb_define_const(mrb, mod_gl2, "GL_REPLACE", mrb_fixnum_value(GL_REPLACE));
  mrb_define_const(mrb, mod_gl2, "GL_INCR", mrb_fixnum_value(GL_INCR));
  mrb_define_const(mrb, mod_gl2, "GL_DECR", mrb_fixnum_value(GL_DECR));
  mrb_define_const(mrb, mod_gl2, "GL_INVERT", mrb_fixnum_value(GL_INVERT));
  mrb_define_const(mrb, mod_gl2, "GL_INCR_WRAP", mrb_fixnum_value(GL_INCR_WRAP));
  mrb_define_const(mrb, mod_gl2, "GL_DECR_WRAP", mrb_fixnum_value(GL_DECR_WRAP));

  mrb_define_const(mrb, mod_gl2, "GL_VENDOR", mrb_fixnum_value(GL_VENDOR));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERER", mrb_fixnum_value(GL_RENDERER));
  mrb_define_const(mrb, mod_gl2, "GL_VERSION", mrb_fixnum_value(GL_VERSION));
  mrb_define_const(mrb, mod_gl2, "GL_EXTENSIONS", mrb_fixnum_value(GL_EXTENSIONS));

  mrb_define_const(mrb, mod_gl2, "GL_NEAREST", mrb_fixnum_value(GL_NEAREST));
  mrb_define_const(mrb, mod_gl2, "GL_LINEAR", mrb_fixnum_value(GL_LINEAR));

  mrb_define_const(mrb, mod_gl2, "GL_NEAREST_MIPMAP_NEAREST", mrb_fixnum_value(GL_NEAREST_MIPMAP_NEAREST));
  mrb_define_const(mrb, mod_gl2, "GL_LINEAR_MIPMAP_NEAREST", mrb_fixnum_value(GL_LINEAR_MIPMAP_NEAREST));
  mrb_define_const(mrb, mod_gl2, "GL_NEAREST_MIPMAP_LINEAR", mrb_fixnum_value(GL_NEAREST_MIPMAP_LINEAR));
  mrb_define_const(mrb, mod_gl2, "GL_LINEAR_MIPMAP_LINEAR", mrb_fixnum_value(GL_LINEAR_MIPMAP_LINEAR));

  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_MAG_FILTER", mrb_fixnum_value(GL_TEXTURE_MAG_FILTER));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_MIN_FILTER", mrb_fixnum_value(GL_TEXTURE_MIN_FILTER));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_WRAP_S", mrb_fixnum_value(GL_TEXTURE_WRAP_S));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_WRAP_T", mrb_fixnum_value(GL_TEXTURE_WRAP_T));

  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE", mrb_fixnum_value(GL_TEXTURE));

  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_CUBE_MAP", mrb_fixnum_value(GL_TEXTURE_CUBE_MAP));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_BINDING_CUBE_MAP", mrb_fixnum_value(GL_TEXTURE_BINDING_CUBE_MAP));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_CUBE_MAP_POSITIVE_X", mrb_fixnum_value(GL_TEXTURE_CUBE_MAP_POSITIVE_X));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_CUBE_MAP_NEGATIVE_X", mrb_fixnum_value(GL_TEXTURE_CUBE_MAP_NEGATIVE_X));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_CUBE_MAP_POSITIVE_Y", mrb_fixnum_value(GL_TEXTURE_CUBE_MAP_POSITIVE_Y));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Y", mrb_fixnum_value(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_CUBE_MAP_POSITIVE_Z", mrb_fixnum_value(GL_TEXTURE_CUBE_MAP_POSITIVE_Z));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE_CUBE_MAP_NEGATIVE_Z", mrb_fixnum_value(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_CUBE_MAP_TEXTURE_SIZE", mrb_fixnum_value(GL_MAX_CUBE_MAP_TEXTURE_SIZE));

  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE0", mrb_fixnum_value(GL_TEXTURE0));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE1", mrb_fixnum_value(GL_TEXTURE1));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE2", mrb_fixnum_value(GL_TEXTURE2));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE3", mrb_fixnum_value(GL_TEXTURE3));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE4", mrb_fixnum_value(GL_TEXTURE4));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE5", mrb_fixnum_value(GL_TEXTURE5));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE6", mrb_fixnum_value(GL_TEXTURE6));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE7", mrb_fixnum_value(GL_TEXTURE7));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE8", mrb_fixnum_value(GL_TEXTURE8));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE9", mrb_fixnum_value(GL_TEXTURE9));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE10", mrb_fixnum_value(GL_TEXTURE10));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE11", mrb_fixnum_value(GL_TEXTURE11));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE12", mrb_fixnum_value(GL_TEXTURE12));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE13", mrb_fixnum_value(GL_TEXTURE13));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE14", mrb_fixnum_value(GL_TEXTURE14));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE15", mrb_fixnum_value(GL_TEXTURE15));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE16", mrb_fixnum_value(GL_TEXTURE16));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE17", mrb_fixnum_value(GL_TEXTURE17));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE18", mrb_fixnum_value(GL_TEXTURE18));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE19", mrb_fixnum_value(GL_TEXTURE19));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE20", mrb_fixnum_value(GL_TEXTURE20));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE21", mrb_fixnum_value(GL_TEXTURE21));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE22", mrb_fixnum_value(GL_TEXTURE22));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE23", mrb_fixnum_value(GL_TEXTURE23));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE24", mrb_fixnum_value(GL_TEXTURE24));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE25", mrb_fixnum_value(GL_TEXTURE25));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE26", mrb_fixnum_value(GL_TEXTURE26));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE27", mrb_fixnum_value(GL_TEXTURE27));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE28", mrb_fixnum_value(GL_TEXTURE28));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE29", mrb_fixnum_value(GL_TEXTURE29));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE30", mrb_fixnum_value(GL_TEXTURE30));
  mrb_define_const(mrb, mod_gl2, "GL_TEXTURE31", mrb_fixnum_value(GL_TEXTURE31));
  mrb_define_const(mrb, mod_gl2, "GL_ACTIVE_TEXTURE", mrb_fixnum_value(GL_ACTIVE_TEXTURE));

  mrb_define_const(mrb, mod_gl2, "GL_REPEAT", mrb_fixnum_value(GL_REPEAT));
  mrb_define_const(mrb, mod_gl2, "GL_CLAMP_TO_EDGE", mrb_fixnum_value(GL_CLAMP_TO_EDGE));
  mrb_define_const(mrb, mod_gl2, "GL_MIRRORED_REPEAT", mrb_fixnum_value(GL_MIRRORED_REPEAT));

  mrb_define_const(mrb, mod_gl2, "GL_FLOAT_VEC2", mrb_fixnum_value(GL_FLOAT_VEC2));
  mrb_define_const(mrb, mod_gl2, "GL_FLOAT_VEC3", mrb_fixnum_value(GL_FLOAT_VEC3));
  mrb_define_const(mrb, mod_gl2, "GL_FLOAT_VEC4", mrb_fixnum_value(GL_FLOAT_VEC4));
  mrb_define_const(mrb, mod_gl2, "GL_INT_VEC2", mrb_fixnum_value(GL_INT_VEC2));
  mrb_define_const(mrb, mod_gl2, "GL_INT_VEC3", mrb_fixnum_value(GL_INT_VEC3));
  mrb_define_const(mrb, mod_gl2, "GL_INT_VEC4", mrb_fixnum_value(GL_INT_VEC4));
  mrb_define_const(mrb, mod_gl2, "GL_BOOL", mrb_fixnum_value(GL_BOOL));
  mrb_define_const(mrb, mod_gl2, "GL_BOOL_VEC2", mrb_fixnum_value(GL_BOOL_VEC2));
  mrb_define_const(mrb, mod_gl2, "GL_BOOL_VEC3", mrb_fixnum_value(GL_BOOL_VEC3));
  mrb_define_const(mrb, mod_gl2, "GL_BOOL_VEC4", mrb_fixnum_value(GL_BOOL_VEC4));
  mrb_define_const(mrb, mod_gl2, "GL_FLOAT_MAT2", mrb_fixnum_value(GL_FLOAT_MAT2));
  mrb_define_const(mrb, mod_gl2, "GL_FLOAT_MAT3", mrb_fixnum_value(GL_FLOAT_MAT3));
  mrb_define_const(mrb, mod_gl2, "GL_FLOAT_MAT4", mrb_fixnum_value(GL_FLOAT_MAT4));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLER_2D", mrb_fixnum_value(GL_SAMPLER_2D));
  mrb_define_const(mrb, mod_gl2, "GL_SAMPLER_CUBE", mrb_fixnum_value(GL_SAMPLER_CUBE));

  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_ATTRIB_ARRAY_ENABLED", mrb_fixnum_value(GL_VERTEX_ATTRIB_ARRAY_ENABLED));
  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_ATTRIB_ARRAY_SIZE", mrb_fixnum_value(GL_VERTEX_ATTRIB_ARRAY_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_ATTRIB_ARRAY_STRIDE", mrb_fixnum_value(GL_VERTEX_ATTRIB_ARRAY_STRIDE));
  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_ATTRIB_ARRAY_TYPE", mrb_fixnum_value(GL_VERTEX_ATTRIB_ARRAY_TYPE));
  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_ATTRIB_ARRAY_NORMALIZED", mrb_fixnum_value(GL_VERTEX_ATTRIB_ARRAY_NORMALIZED));
  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_ATTRIB_ARRAY_POINTER", mrb_fixnum_value(GL_VERTEX_ATTRIB_ARRAY_POINTER));
  mrb_define_const(mrb, mod_gl2, "GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING", mrb_fixnum_value(GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING));

  mrb_define_const(mrb, mod_gl2, "GL_IMPLEMENTATION_COLOR_READ_TYPE", mrb_fixnum_value(GL_IMPLEMENTATION_COLOR_READ_TYPE));
  mrb_define_const(mrb, mod_gl2, "GL_IMPLEMENTATION_COLOR_READ_FORMAT", mrb_fixnum_value(GL_IMPLEMENTATION_COLOR_READ_FORMAT));

  mrb_define_const(mrb, mod_gl2, "GL_COMPILE_STATUS", mrb_fixnum_value(GL_COMPILE_STATUS));
  mrb_define_const(mrb, mod_gl2, "GL_INFO_LOG_LENGTH", mrb_fixnum_value(GL_INFO_LOG_LENGTH));
  mrb_define_const(mrb, mod_gl2, "GL_SHADER_SOURCE_LENGTH", mrb_fixnum_value(GL_SHADER_SOURCE_LENGTH));
  mrb_define_const(mrb, mod_gl2, "GL_SHADER_COMPILER", mrb_fixnum_value(GL_SHADER_COMPILER));

  mrb_define_const(mrb, mod_gl2, "GL_SHADER_BINARY_FORMATS", mrb_fixnum_value(GL_SHADER_BINARY_FORMATS));
  mrb_define_const(mrb, mod_gl2, "GL_NUM_SHADER_BINARY_FORMATS", mrb_fixnum_value(GL_NUM_SHADER_BINARY_FORMATS));

  mrb_define_const(mrb, mod_gl2, "GL_LOW_FLOAT", mrb_fixnum_value(GL_LOW_FLOAT));
  mrb_define_const(mrb, mod_gl2, "GL_MEDIUM_FLOAT", mrb_fixnum_value(GL_MEDIUM_FLOAT));
  mrb_define_const(mrb, mod_gl2, "GL_HIGH_FLOAT", mrb_fixnum_value(GL_HIGH_FLOAT));
  mrb_define_const(mrb, mod_gl2, "GL_LOW_INT", mrb_fixnum_value(GL_LOW_INT));
  mrb_define_const(mrb, mod_gl2, "GL_MEDIUM_INT", mrb_fixnum_value(GL_MEDIUM_INT));
  mrb_define_const(mrb, mod_gl2, "GL_HIGH_INT", mrb_fixnum_value(GL_HIGH_INT));

  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER", mrb_fixnum_value(GL_FRAMEBUFFER));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER", mrb_fixnum_value(GL_RENDERBUFFER));

  mrb_define_const(mrb, mod_gl2, "GL_RGBA4", mrb_fixnum_value(GL_RGBA4));
  mrb_define_const(mrb, mod_gl2, "GL_RGB5_A1", mrb_fixnum_value(GL_RGB5_A1));
  mrb_define_const(mrb, mod_gl2, "GL_RGB565", mrb_fixnum_value(GL_RGB565));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_COMPONENT16", mrb_fixnum_value(GL_DEPTH_COMPONENT16));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_INDEX", mrb_fixnum_value(GL_STENCIL_INDEX));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_INDEX8", mrb_fixnum_value(GL_STENCIL_INDEX8));

  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_WIDTH", mrb_fixnum_value(GL_RENDERBUFFER_WIDTH));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_HEIGHT", mrb_fixnum_value(GL_RENDERBUFFER_HEIGHT));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_INTERNAL_FORMAT", mrb_fixnum_value(GL_RENDERBUFFER_INTERNAL_FORMAT));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_RED_SIZE", mrb_fixnum_value(GL_RENDERBUFFER_RED_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_GREEN_SIZE", mrb_fixnum_value(GL_RENDERBUFFER_GREEN_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_BLUE_SIZE", mrb_fixnum_value(GL_RENDERBUFFER_BLUE_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_ALPHA_SIZE", mrb_fixnum_value(GL_RENDERBUFFER_ALPHA_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_DEPTH_SIZE", mrb_fixnum_value(GL_RENDERBUFFER_DEPTH_SIZE));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_STENCIL_SIZE", mrb_fixnum_value(GL_RENDERBUFFER_STENCIL_SIZE));

  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE", mrb_fixnum_value(GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE));
  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME", mrb_fixnum_value(GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME));
  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL", mrb_fixnum_value(GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL));
  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE", mrb_fixnum_value(GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE));

  mrb_define_const(mrb, mod_gl2, "GL_COLOR_ATTACHMENT0", mrb_fixnum_value(GL_COLOR_ATTACHMENT0));
  mrb_define_const(mrb, mod_gl2, "GL_DEPTH_ATTACHMENT", mrb_fixnum_value(GL_DEPTH_ATTACHMENT));
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_ATTACHMENT", mrb_fixnum_value(GL_STENCIL_ATTACHMENT));

  mrb_define_const(mrb, mod_gl2, "GL_NONE", mrb_fixnum_value(GL_NONE));

  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_COMPLETE", mrb_fixnum_value(GL_FRAMEBUFFER_COMPLETE));
  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT", mrb_fixnum_value(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT));
  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT", mrb_fixnum_value(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT));
  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS", mrb_fixnum_value(GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS));
  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_UNSUPPORTED", mrb_fixnum_value(GL_FRAMEBUFFER_UNSUPPORTED));

  mrb_define_const(mrb, mod_gl2, "GL_FRAMEBUFFER_BINDING", mrb_fixnum_value(GL_FRAMEBUFFER_BINDING));
  mrb_define_const(mrb, mod_gl2, "GL_RENDERBUFFER_BINDING", mrb_fixnum_value(GL_RENDERBUFFER_BINDING));
  mrb_define_const(mrb, mod_gl2, "GL_MAX_RENDERBUFFER_SIZE", mrb_fixnum_value(GL_MAX_RENDERBUFFER_SIZE));

  mrb_define_const(mrb, mod_gl2, "GL_INVALID_FRAMEBUFFER_OPERATION", mrb_fixnum_value(GL_INVALID_FRAMEBUFFER_OPERATION));

  /* GL core functions */
}
