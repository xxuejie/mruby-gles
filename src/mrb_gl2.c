#include <stdarg.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/string.h>

#include <GLES2/gl2.h>

#define MRB_VALUE_TO_GL_BOOLEAN(v_) ((mrb_test(v_)) ? (GL_TRUE) : (GL_FALSE))
#define GL_BOOLEAN_TO_MRB_VALUE(v_) (((v_) == GL_TRUE) ? (mrb_true_value()) : \
                                     (mrb_false_value()))

void* allocate_buffer(mrb_state* mrb, int len, int item_size)
{
  void* p;

  if (len <= 0) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Buffer length is not positive number!");
  }

  p = malloc(len * item_size);
  if (p == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Cannot allocate memory!");
  }

  return p;
}

#define allocate_uint_buffer(mrb, len) (GLuint*) \
  allocate_buffer(mrb, len, sizeof(GLuint))
#define allocate_char_buffer(mrb, len) (GLchar*) \
  allocate_buffer(mrb, len, sizeof(GLchar))
#define allocate_boolean_buffer(mrb, len) (GLboolean*) \
  allocate_buffer(mrb, len, sizeof(GLboolean))
#define allocate_float_buffer(mrb, len) (GLfloat*) \
  allocate_buffer(mrb, len, sizeof(GLfloat))
#define allocate_int_buffer(mrb, len) (GLint*) \
  allocate_buffer(mrb, len, sizeof(GLint))
#define allocate_char_p_buffer(mrb, len) (GLchar**) \
  allocate_buffer(mrb, len, sizeof(GLchar*))

void release_buffer(mrb_state* mrb, void* p)
{
  free(p);
}

GLuint* mrb_array_to_uint_buffer(mrb_state* mrb, mrb_value arr)
{
  int i;
  GLuint* p = allocate_uint_buffer(mrb, RARRAY_LEN(arr));

  for (i = 0; i < RARRAY_LEN(arr); i++) {
    p[i] = mrb_fixnum(RARRAY_PTR(arr)[i]);
  }

  return p;
}

GLint* mrb_array_to_int_buffer(mrb_state* mrb, mrb_value arr)
{
  int i;
  GLint* p = allocate_int_buffer(mrb, RARRAY_LEN(arr));

  for (i = 0; i < RARRAY_LEN(arr); i++) {
    p[i] = mrb_fixnum(RARRAY_PTR(arr)[i]);
  }

  return p;
}

GLfloat* mrb_array_to_float_buffer(mrb_state* mrb, mrb_value arr)
{
  int i;
  GLfloat* p = allocate_float_buffer(mrb, RARRAY_LEN(arr));

  for (i = 0; i < RARRAY_LEN(arr); i++) {
    p[i] = mrb_float(RARRAY_PTR(arr)[i]);
  }

  return p;
}

GLchar** mrb_array_to_char_p_buffer(mrb_state* mrb, mrb_value arr)
{
  int i;
  GLchar** p = allocate_char_p_buffer(mrb, RARRAY_LEN(arr));

  for (i = 0; i < RARRAY_LEN(arr); i++) {
    p[i] = mrb_string_value_cstr(mrb, &RARRAY_PTR(arr)[i]);
  }

  return p;
}

mrb_value uint_buffer_to_mrb_array(mrb_state* mrb, const GLuint* p, int len)
{
  int i;
  mrb_value arr = mrb_ary_new_capa(mrb, len);

  for (i = 0; i < len; i++) {
    mrb_ary_push(mrb, arr, mrb_fixnum_value(p[i]));
  }

  return arr;
}

mrb_value boolean_buffer_to_mrb_array(mrb_state* mrb, const GLboolean* p, int len)
{
  int i;
  mrb_value arr = mrb_ary_new_capa(mrb, len);

  for (i = 0; i < len; i++) {
    mrb_ary_push(mrb, arr, GL_BOOLEAN_TO_MRB_VALUE(p[i]));
  }

  return arr;
}

mrb_value float_buffer_to_mrb_array(mrb_state* mrb, const GLfloat* p, int len)
{
  int i;
  mrb_value arr = mrb_ary_new_capa(mrb, len);

  for (i = 0; i < len; i++) {
    mrb_ary_push(mrb, arr, mrb_float_value(mrb, p[i]));
  }

  return arr;
}

mrb_value int_buffer_to_mrb_array(mrb_state* mrb, const GLint* p, int len)
{
  int i;
  mrb_value arr = mrb_ary_new_capa(mrb, len);

  for (i = 0; i < len; i++) {
    mrb_ary_push(mrb, arr, mrb_fixnum_value(p[i]));
  }

  return arr;
}

mrb_value mrb_ary_newv(mrb_state *mrb, int n, ...)
{
  int i;
  va_list ap;
  mrb_value ret = mrb_ary_new_capa(mrb, n);

  va_start(ap, n);
  for (i = 0; i < n; i++) {
    mrb_ary_push(mrb, ret, va_arg(ap, mrb_value));
  }
  va_end(ap);

  return ret;
}

int gl_get_argument_number(GLenum name)
{
  int n = -1;
  switch (name) {
    case GL_ACTIVE_TEXTURE:
    case GL_ALPHA_BITS:
    case GL_ARRAY_BUFFER_BINDING:
    case GL_BLEND:
    case GL_BLEND_DST_ALPHA:
    case GL_BLEND_DST_RGB:
    case GL_BLEND_EQUATION_ALPHA:
    case GL_BLEND_EQUATION_RGB:
    case GL_BLEND_SRC_ALPHA:
    case GL_BLEND_SRC_RGB:
    case GL_BLUE_BITS:
    case GL_CULL_FACE:
    case GL_CULL_FACE_MODE:
    case GL_CURRENT_PROGRAM:
    case GL_DEPTH_BITS:
    case GL_DEPTH_CLEAR_VALUE:
    case GL_DEPTH_FUNC:
    case GL_DEPTH_TEST:
    case GL_DEPTH_WRITEMASK:
    case GL_DITHER:
    case GL_ELEMENT_ARRAY_BUFFER_BINDING:
    case GL_FRAMEBUFFER_BINDING:
    case GL_FRONT_FACE:
    case GL_GENERATE_MIPMAP_HINT:
    case GL_GREEN_BITS:
    case GL_IMPLEMENTATION_COLOR_READ_FORMAT:
    case GL_IMPLEMENTATION_COLOR_READ_TYPE:
    case GL_LINE_WIDTH:
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
    case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
    case GL_MAX_RENDERBUFFER_SIZE:
    case GL_MAX_TEXTURE_IMAGE_UNITS:
    case GL_MAX_TEXTURE_SIZE:
    case GL_MAX_VARYING_VECTORS:
    case GL_MAX_VERTEX_ATTRIBS:
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
    case GL_MAX_VERTEX_UNIFORM_VECTORS:
    case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
    case GL_NUM_SHADER_BINARY_FORMATS:
    case GL_PACK_ALIGNMENT:
    case GL_POLYGON_OFFSET_FACTOR:
    case GL_POLYGON_OFFSET_FILL:
    case GL_POLYGON_OFFSET_UNITS:
    case GL_RED_BITS:
    case GL_RENDERBUFFER_BINDING:
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
    case GL_SAMPLE_BUFFERS:
    case GL_SAMPLE_COVERAGE:
    case GL_SAMPLE_COVERAGE_INVERT:
    case GL_SAMPLE_COVERAGE_VALUE:
    case GL_SAMPLES:
    case GL_SCISSOR_TEST:
    case GL_SHADER_COMPILER:
    case GL_STENCIL_BACK_FAIL:
    case GL_STENCIL_BACK_FUNC:
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL:
    case GL_STENCIL_BACK_PASS_DEPTH_PASS:
    case GL_STENCIL_BACK_REF:
    case GL_STENCIL_BACK_VALUE_MASK:
    case GL_STENCIL_BACK_WRITEMASK:
    case GL_STENCIL_BITS:
    case GL_STENCIL_CLEAR_VALUE:
    case GL_STENCIL_FAIL:
    case GL_STENCIL_FUNC:
    case GL_STENCIL_PASS_DEPTH_FAIL:
    case GL_STENCIL_PASS_DEPTH_PASS:
    case GL_STENCIL_REF:
    case GL_STENCIL_TEST:
    case GL_STENCIL_VALUE_MASK:
    case GL_STENCIL_WRITEMASK:
    case GL_SUBPIXEL_BITS:
    case GL_TEXTURE_BINDING_2D:
    case GL_TEXTURE_BINDING_CUBE_MAP:
    case GL_UNPACK_ALIGNMENT:
      n = 1;
      break;
    case GL_ALIASED_LINE_WIDTH_RANGE:
    case GL_ALIASED_POINT_SIZE_RANGE:
    case GL_DEPTH_RANGE:
    case GL_MAX_VIEWPORT_DIMS:
      n = 2;
      break;
    case GL_BLEND_COLOR:
    case GL_COLOR_CLEAR_VALUE:
    case GL_COLOR_WRITEMASK:
    case GL_SCISSOR_BOX:
    case GL_VIEWPORT:
      n = 4;
      break;
    case GL_COMPRESSED_TEXTURE_FORMATS:
      n = GL_NUM_COMPRESSED_TEXTURE_FORMATS;
      break;
    case GL_SHADER_BINARY_FORMATS:
      n = GL_NUM_SHADER_BINARY_FORMATS;
      break;
  }
  return n;
}

int gl_get_vertex_attrib_number(GLenum name)
{
  int n = -1;
  switch (name) {
    case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
    case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
    case GL_VERTEX_ATTRIB_ARRAY_SIZE:
    case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
    case GL_VERTEX_ATTRIB_ARRAY_TYPE:
    case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
      n = 1;
      break;
    case GL_CURRENT_VERTEX_ATTRIB:
      n = 4;
      break;
  }
  return n;
}

static struct RClass *mod_gl2;

static mrb_value
mrb_gl_active_texture(mrb_state* mrb, mrb_value mod)
{
  mrb_int texture;

  mrb_get_args(mrb, "i", &texture);
  glActiveTexture((GLenum) texture);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_attach_shader(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, shader;

  mrb_get_args(mrb, "ii", &program, &shader);
  glAttachShader((GLuint) program, (GLuint) shader);

  return mrb_nil_value();
}
static mrb_value
mrb_gl_bind_attrib_location(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, index;
  char* name;

  mrb_get_args(mrb, "iiz", &program, &index, &name);
  glBindAttribLocation((GLuint) program, (GLuint) index, (const GLchar*) name);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_bind_buffer(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, buffer;

  mrb_get_args(mrb, "ii", &target, &buffer);
  glBindBuffer((GLenum) target, (GLuint) buffer);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_bind_framebuffer(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, framebuffer;

  mrb_get_args(mrb, "ii", &target, &framebuffer);
  glBindFramebuffer((GLenum) target, (GLuint) framebuffer);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_bind_renderbuffer(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, renderbuffer;

  mrb_get_args(mrb, "ii", &target, &renderbuffer);
  glBindRenderbuffer((GLenum) target, (GLuint) renderbuffer);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_bind_texture(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, texture;

  mrb_get_args(mrb, "ii", &target, &texture);
  glBindTexture((GLenum) target, (GLuint) texture);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_blend_color(mrb_state* mrb, mrb_value mod)
{
  mrb_float red, green, blue, alpha;

  mrb_get_args(mrb, "ffff", &red, &green, &blue, &alpha);
  glBlendColor((GLclampf) red, (GLclampf) green, (GLclampf) blue, (GLclampf) alpha);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_blend_equation(mrb_state* mrb, mrb_value mod)
{
  mrb_int mode;

  mrb_get_args(mrb, "i", &mode);
  glBlendEquation((GLenum) mode);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_blend_equation_separate(mrb_state* mrb, mrb_value mod)
{
  mrb_int modeRGB, modeAlpha;

  mrb_get_args(mrb, "ii", &modeRGB, &modeAlpha);
  glBlendEquationSeparate((GLenum) modeRGB, (GLenum) modeAlpha);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_blend_func(mrb_state* mrb, mrb_value mod)
{
  mrb_int sfactor, dfactor;

  mrb_get_args(mrb, "ii", &sfactor, &dfactor);
  glBlendFunc((GLenum) sfactor, (GLenum) dfactor);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_blend_func_separate(mrb_state* mrb, mrb_value mod)
{
  mrb_int srcRGB, dstRGB, srcAlpha, dstAlpha;

  mrb_get_args(mrb, "iiii", &srcRGB, &dstRGB, &srcAlpha, &dstAlpha);
  glBlendFuncSeparate((GLenum) srcRGB, (GLenum) dstRGB,
                      (GLenum) srcAlpha, (GLenum) dstAlpha);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_buffer_data(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, size, usage;
  /* NOTE: GLvoid* type is interpreted as a string here,
   * I will write a mrbgem containing Array#pack and
   * String#unpack method for mruby to help with this conversion
   */
  char* data;
  int data_len;

  mrb_get_args(mrb, "iisi", &target, &size, &data, &data_len, &usage);
  glBufferData((GLenum) target, (GLsizeiptr) size,
               (const GLvoid*) data, (GLenum) usage);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_buffer_sub_data(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, offset, size;
  char* data;
  int data_len;

  mrb_get_args(mrb, "iiis", &target, &offset, &size, &data, &data_len);
  glBufferSubData((GLenum) target, (GLintptr) offset,
                  (GLsizeiptr) size, (const GLvoid*) data);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_check_framebuffer_status(mrb_state* mrb, mrb_value mod)
{
  mrb_int target;

  mrb_get_args(mrb, "i", &target);
  return mrb_fixnum_value(glCheckFramebufferStatus((GLenum) target));
}

static mrb_value
mrb_gl_clear(mrb_state* mrb, mrb_value mod)
{
  mrb_int mask;

  mrb_get_args(mrb, "i", &mask);
  glClear((GLbitfield) mask);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_clear_color(mrb_state* mrb, mrb_value mod)
{
  mrb_float red, green, blue, alpha;

  mrb_get_args(mrb, "ffff", &red, &green, &blue, &alpha);
  glClearColor((GLclampf) red, (GLclampf) green,
               (GLclampf) blue, (GLclampf) alpha);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_clear_depthf(mrb_state* mrb, mrb_value mod)
{
  mrb_float depth;

  mrb_get_args(mrb, "f", &depth);
  glClearDepthf((GLclampf) depth);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_clear_stencil(mrb_state* mrb, mrb_value mod)
{
  mrb_int s;

  mrb_get_args(mrb, "i", &s);
  glClearDepthf((GLclampf) s);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_color_mask(mrb_state* mrb, mrb_value mod)
{
  mrb_value red, green, blue, alpha;

  mrb_get_args(mrb, "oooo", &red, &green, &blue, &alpha);
  glColorMask(MRB_VALUE_TO_GL_BOOLEAN(red), MRB_VALUE_TO_GL_BOOLEAN(green),
              MRB_VALUE_TO_GL_BOOLEAN(blue), MRB_VALUE_TO_GL_BOOLEAN(alpha));

  return mrb_nil_value();
}

static mrb_value
mrb_gl_compile_shader(mrb_state* mrb, mrb_value mod)
{
  mrb_int shader;

  mrb_get_args(mrb, "i", &shader);
  glCompileShader((GLuint) shader);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_compressed_tex_image_2d(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, level, internalformat, width, height, border, imageSize;
  char* data;
  int data_len;

  mrb_get_args(mrb, "iiiiiiis", &target, &level, &internalformat, &width,
               &height, &border, &imageSize, &data, &data_len);
  glCompressedTexImage2D((GLenum) target, (GLint) level,
                         (GLenum) internalformat, (GLsizei) width,
                         (GLsizei) height, (GLint) border,
                         (GLsizei) imageSize, (const GLvoid*) data);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_compressed_tex_sub_image_2d(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, level, xoffset, yoffset;
  mrb_int width, height, format, imageSize;
  char* data;
  int data_len;

  mrb_get_args(mrb, "iiiiiiiis", &target, &level, &xoffset, &yoffset,
               &width, &height, &format, &imageSize, &data, &data_len);
  glCompressedTexSubImage2D((GLenum) format, (GLint) level, (GLint) xoffset,
                            (GLint) yoffset, (GLsizei) width, (GLsizei) height,
                            (GLenum) format, (GLsizei) imageSize,
                            (const GLvoid*) data);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_copy_tex_image_2d(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, level, internalformat, x, y, width, height, border;

  mrb_get_args(mrb, "iiiiiiii", &target, &level, &internalformat, &x, &y,
               &width, &height, &border);
  glCopyTexImage2D((GLenum) target, (GLint) level, (GLenum) internalformat,
                   (GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height,
                   (GLint) border);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_copy_tex_sub_image_2d(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, level, xoffset, yoffset, x, y, width, height;

  mrb_get_args(mrb, "iiiiiiii", &target, &level, &xoffset, &yoffset,
               &x, &y, &width, &height);
  glCopyTexSubImage2D((GLenum) target, (GLint) level, (GLint) xoffset,
                      (GLint) yoffset, (GLint) x, (GLint) y,
                      (GLsizei) width, (GLsizei) height);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_create_program(mrb_state* mrb, mrb_value mod)
{
  return mrb_fixnum_value(glCreateProgram());
}

static mrb_value
mrb_gl_create_shader(mrb_state* mrb, mrb_value mod)
{
  mrb_int type;

  mrb_get_args(mrb, "i", &type);
  return mrb_fixnum_value(glCreateShader((GLenum) type));
}

static mrb_value
mrb_gl_cull_face(mrb_state* mrb, mrb_value mod)
{
  mrb_int mode;

  mrb_get_args(mrb, "i", &mode);
  glCullFace((GLenum) mode);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_delete_buffers(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  mrb_value buffers;
  GLuint* buffers_ptr;

  mrb_get_args(mrb, "iA", &n, &buffers);
  buffers_ptr = mrb_array_to_uint_buffer(mrb, buffers);

  glDeleteBuffers((GLsizei) n, buffers_ptr);

  release_buffer(mrb, buffers_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_delete_framebuffers(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  mrb_value framebuffers;
  GLuint* framebuffers_ptr;

  mrb_get_args(mrb, "iA", &n, &framebuffers);
  framebuffers_ptr = mrb_array_to_uint_buffer(mrb, framebuffers);

  glDeleteFramebuffers((GLsizei) n, framebuffers_ptr);

  release_buffer(mrb, framebuffers_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_delete_program(mrb_state* mrb, mrb_value mod)
{
  mrb_int program;

  mrb_get_args(mrb, "i", &program);

  glDeleteProgram((GLuint) program);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_delete_renderbuffers(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  mrb_value renderbuffers;
  GLuint* renderbuffers_ptr;

  mrb_get_args(mrb, "iA", &n, &renderbuffers);
  renderbuffers_ptr = mrb_array_to_uint_buffer(mrb, renderbuffers);

  glDeleteRenderbuffers((GLsizei) n, renderbuffers_ptr);

  release_buffer(mrb, renderbuffers_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_delete_shader(mrb_state* mrb, mrb_value mod)
{
  mrb_int shader;

  mrb_get_args(mrb, "i", &shader);
  glDeleteShader((GLuint) shader);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_delete_textures(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  mrb_value textures;
  GLuint* textures_ptr;

  mrb_get_args(mrb, "iA", &n, &textures);
  textures_ptr = mrb_array_to_uint_buffer(mrb, textures);

  glDeleteTextures((GLsizei) n, textures_ptr);

  release_buffer(mrb, textures_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_depth_func(mrb_state* mrb, mrb_value mod)
{
  mrb_int func;

  mrb_get_args(mrb, "i", &func);
  glDepthFunc((GLenum) func);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_depth_mask(mrb_state* mrb, mrb_value mod)
{
  mrb_value flag;

  mrb_get_args(mrb, "o", &flag);
  glDepthMask(MRB_VALUE_TO_GL_BOOLEAN(flag));

  return mrb_nil_value();
}

static mrb_value
mrb_gl_depth_rangef(mrb_state* mrb, mrb_value mod)
{
  mrb_float zNear, zFar;

  mrb_get_args(mrb, "ff", &zNear, &zFar);
  glDepthRangef((GLclampf) zNear, (GLclampf) zFar);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_detach_shader(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, shader;

  mrb_get_args(mrb, "ii", &program, &shader);
  glDetachShader((GLuint) program, (GLuint) shader);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_disable(mrb_state* mrb, mrb_value mod)
{
  mrb_int cap;

  mrb_get_args(mrb, "i", &cap);
  glDisable((GLenum) cap);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_disable_vertex_attrib_array(mrb_state* mrb, mrb_value mod)
{
  mrb_int index;

  mrb_get_args(mrb, "i", &index);
  glDisableVertexAttribArray((GLuint) index);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_draw_arrays(mrb_state* mrb, mrb_value mod)
{
  mrb_int mode, first, count;

  mrb_get_args(mrb, "iii", &mode, &first, &count);
  glDrawArrays((GLenum) mode, (GLint) first, (GLsizei) count);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_draw_elements(mrb_state* mrb, mrb_value mod)
{
  mrb_int mode, count, type;
  char* indices;
  int indices_len;

  mrb_get_args(mrb, "iiis", &mode, &count, &type, &indices, &indices_len);
  glDrawElements((GLenum) mode, (GLsizei) count, (GLenum) type,
                 (const GLvoid*) indices);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_enable(mrb_state* mrb, mrb_value mod)
{
  mrb_int cap;

  mrb_get_args(mrb, "i", &cap);
  glEnable((GLenum) cap);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_enable_vertex_attrib_array(mrb_state* mrb, mrb_value mod)
{
  mrb_int index;

  mrb_get_args(mrb, "i", &index);
  glEnableVertexAttribArray((GLuint) index);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_finish(mrb_state* mrb, mrb_value mod)
{
  glFinish();
  return mrb_nil_value();
}

static mrb_value
mrb_gl_flush(mrb_state* mrb, mrb_value mod)
{
  glFlush();
  return mrb_nil_value();
}

static mrb_value
mrb_gl_framebuffer_renderbuffer(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, attachment, renderbuffertarget, renderbuffer;

  mrb_get_args(mrb, "iiii", &target, &attachment, &renderbuffertarget,
               &renderbuffer);
  glFramebufferRenderbuffer((GLenum) target, (GLenum) attachment,
                            (GLenum) renderbuffertarget,
                            (GLenum) renderbuffer);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_framebuffer_texture_2d(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, attachment, textarget, texture, level;

  mrb_get_args(mrb, "iiiii", &target, &attachment, &textarget, &texture,
               &level);
  glFramebufferTexture2D((GLenum) target, (GLenum) attachment,
                         (GLenum) textarget, (GLuint) texture, (GLint) level);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_front_face(mrb_state* mrb, mrb_value mod)
{
  mrb_int mode;

  mrb_get_args(mrb, "i", &mode);
  glFrontFace((GLenum) mode);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_gen_buffers(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  GLuint* buffers_ptr;
  mrb_value buffers;

  mrb_get_args(mrb, "i", &n);
  buffers_ptr = allocate_uint_buffer(mrb, n);

  glGenBuffers((GLsizei) n, buffers_ptr);

  buffers = uint_buffer_to_mrb_array(mrb, buffers_ptr, n);
  release_buffer(mrb, buffers_ptr);

  return buffers;
}

static mrb_value
mrb_gl_generate_mipmap(mrb_state* mrb, mrb_value mod)
{
  mrb_int target;

  mrb_get_args(mrb, "i", &target);
  glGenerateMipmap((GLenum) target);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_gen_framebuffers(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  GLuint* framebuffers_ptr;
  mrb_value framebuffers;

  mrb_get_args(mrb, "i", &n);
  framebuffers_ptr = allocate_uint_buffer(mrb, n);

  glGenFramebuffers((GLsizei) n, framebuffers_ptr);

  framebuffers = uint_buffer_to_mrb_array(mrb, framebuffers_ptr, n);
  release_buffer(mrb, framebuffers_ptr);

  return framebuffers;
}

static mrb_value
mrb_gl_gen_renderbuffers(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  GLuint* renderbuffers_ptr;
  mrb_value renderbuffers;

  mrb_get_args(mrb, "i", &n);
  renderbuffers_ptr = allocate_uint_buffer(mrb, n);

  glGenRenderbuffers((GLsizei) n, renderbuffers_ptr);

  renderbuffers = uint_buffer_to_mrb_array(mrb, renderbuffers_ptr, n);
  release_buffer(mrb, renderbuffers_ptr);

  return renderbuffers;
}

static mrb_value
mrb_gl_gen_textures(mrb_state* mrb, mrb_value mod)
{
  mrb_int n;
  GLuint* textures_ptr;
  mrb_value textures;

  mrb_get_args(mrb, "i", &n);
  textures_ptr = allocate_uint_buffer(mrb, n);

  glGenTextures((GLsizei) n, textures_ptr);

  textures = uint_buffer_to_mrb_array(mrb, textures_ptr, n);
  release_buffer(mrb, textures_ptr);

  return textures;
}

static mrb_value
mrb_gl_get_active_attrib(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, index, bufsize;
  GLsizei length;
  GLint size;
  GLenum type;
  GLchar* name_ptr;
  mrb_value name;

  mrb_get_args(mrb, "iii", &program, &index, &bufsize);
  name_ptr = allocate_char_buffer(mrb, bufsize);

  glGetActiveAttrib((GLuint) program, (GLuint) index, (GLsizei) bufsize,
                    &length, &size, &type, name_ptr);

  name = mrb_str_new_cstr(mrb, name_ptr);
  release_buffer(mrb, name_ptr);

  return mrb_ary_newv(mrb, 4,
                      mrb_fixnum_value(length),
                      mrb_fixnum_value(size),
                      mrb_fixnum_value(type),
                      name);
}

static mrb_value
mrb_gl_get_active_uniform(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, index, bufsize;
  GLsizei length;
  GLint size;
  GLenum type;
  GLchar* name_ptr;
  mrb_value name;

  mrb_get_args(mrb, "iii", &program, &index, &bufsize);
  name_ptr = allocate_char_buffer(mrb, bufsize);

  glGetActiveUniform((GLuint) program, (GLuint) index, (GLsizei) bufsize,
                    &length, &size, &type, name_ptr);

  name = mrb_str_new_cstr(mrb, name_ptr);
  release_buffer(mrb, name_ptr);

  return mrb_ary_newv(mrb, 4,
                      mrb_fixnum_value(length),
                      mrb_fixnum_value(size),
                      mrb_fixnum_value(type),
                      name);
}

static mrb_value
mrb_gl_get_attached_shaders(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, maxcount;
  GLsizei count;
  GLuint* shaders_ptr;
  mrb_value shaders;

  mrb_get_args(mrb, "ii", &program, &maxcount);
  shaders_ptr = allocate_uint_buffer(mrb, maxcount);

  glGetAttachedShaders((GLuint) program, (GLsizei) maxcount,
                       &count, shaders_ptr);

  shaders = uint_buffer_to_mrb_array(mrb, shaders_ptr, count);
  release_buffer(mrb, shaders_ptr);

  return mrb_ary_newv(mrb, 2,
                      mrb_fixnum_value(count),
                      shaders);
}

static mrb_value
mrb_gl_get_attrib_location(mrb_state* mrb, mrb_value mod)
{
  mrb_int program;
  char* name;

  mrb_get_args(mrb, "iz", &program, &name);
  return mrb_fixnum_value(glGetAttribLocation((GLuint) program,
                                                 (const GLchar*) name));
}

static mrb_value
mrb_gl_get_booleanv(mrb_state* mrb, mrb_value mod)
{
  mrb_int pname;
  int params_len;
  GLboolean* params_ptr;
  mrb_value params;

  mrb_get_args(mrb, "i", &pname);
  params_len = gl_get_argument_number((GLenum) pname);
  params_ptr = allocate_boolean_buffer(mrb, params_len);

  glGetBooleanv((GLenum) pname, params_ptr);

  params = boolean_buffer_to_mrb_array(mrb, params_ptr, params_len);
  release_buffer(mrb, params_ptr);

  return params;
}

static mrb_value
mrb_gl_get_buffer_parameteriv(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname;
  GLint params;

  mrb_get_args(mrb, "ii", &target, &pname);
  glGetBufferParameteriv((GLenum) target, (GLenum) pname, &params);

  return mrb_fixnum_value(params);
}

static mrb_value
mrb_gl_get_error(mrb_state* mrb, mrb_value mod)
{
  return mrb_fixnum_value(glGetError());
}

static mrb_value
mrb_gl_get_floatv(mrb_state* mrb, mrb_value mod)
{
  mrb_int pname;
  int params_len;
  GLfloat* params_ptr;
  mrb_value params;

  mrb_get_args(mrb, "i", &pname);
  params_len = gl_get_argument_number((GLenum) pname);
  params_ptr = allocate_float_buffer(mrb, params_len);

  glGetFloatv((GLenum) pname, params_ptr);

  params = float_buffer_to_mrb_array(mrb, params_ptr, params_len);
  release_buffer(mrb, params_ptr);

  return params;
}

static mrb_value
mrb_gl_get_framebuffer_attachment_parameteriv(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, attachment, pname;
  GLint params;

  mrb_get_args(mrb, "iii", &target, &attachment, &pname);
  glGetFramebufferAttachmentParameteriv((GLenum) target, (GLenum) attachment,
                                        (GLenum) pname, &params);

  return mrb_fixnum_value(params);
}

static mrb_value
mrb_gl_get_integerv(mrb_state* mrb, mrb_value mod)
{
  mrb_int pname;
  int params_len;
  GLint* params_ptr;
  mrb_value params;

  mrb_get_args(mrb, "i", &pname);
  params_len = gl_get_argument_number((GLenum) pname);
  params_ptr = allocate_int_buffer(mrb, params_len);

  glGetIntegerv((GLenum) pname, params_ptr);

  params = int_buffer_to_mrb_array(mrb, params_ptr, params_len);
  release_buffer(mrb, params_ptr);

  return params;
}

static mrb_value
mrb_gl_get_programiv(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, pname;
  GLint params;

  mrb_get_args(mrb, "ii", &program, &pname);
  glGetProgramiv((GLuint) program, (GLenum) pname, &params);

  return mrb_fixnum_value(params);
}

static mrb_value
mrb_gl_get_program_info_log(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, bufsize;
  GLsizei length;
  GLchar* infoLog_ptr;
  mrb_value infoLog;

  mrb_get_args(mrb, "ii", &program, &bufsize);
  infoLog_ptr = allocate_char_buffer(mrb, bufsize);

  glGetProgramInfoLog((GLuint) program, (GLsizei) bufsize,
                      &length, infoLog_ptr);

  infoLog = mrb_str_new(mrb, infoLog_ptr, length);
  release_buffer(mrb, infoLog_ptr);

  return mrb_ary_newv(mrb, 2,
                      mrb_fixnum_value(length),
                      infoLog);
}

static mrb_value
mrb_gl_get_renderbuffer_parameteriv(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname;
  GLint params;

  mrb_get_args(mrb, "ii", &target, &pname);
  glGetRenderbufferParameteriv((GLenum) target, (GLenum) pname, &params);

  return mrb_fixnum_value(params);
}

static mrb_value
mrb_gl_get_shaderiv(mrb_state* mrb, mrb_value mod)
{
  mrb_int shader, pname;
  GLint params;

  mrb_get_args(mrb, "ii", &shader, &pname);
  glGetShaderiv((GLuint) shader, (GLenum) pname, &params);

  return mrb_fixnum_value(params);
}

static mrb_value
mrb_gl_get_shader_info_log(mrb_state* mrb, mrb_value mod)
{
  mrb_int shader, bufsize;
  GLsizei length;
  GLchar* infoLog_ptr;
  mrb_value infoLog;

  mrb_get_args(mrb, "ii", &shader, &bufsize);
  infoLog_ptr = allocate_char_buffer(mrb, bufsize);

  glGetShaderInfoLog((GLuint) shader, (GLsizei) bufsize,
                      &length, infoLog_ptr);

  infoLog = mrb_str_new(mrb, infoLog_ptr, length);
  release_buffer(mrb, infoLog_ptr);

  return mrb_ary_newv(mrb, 2,
                      mrb_fixnum_value(length),
                      infoLog);
}

static mrb_value
mrb_gl_get_shader_precision_format(mrb_state* mrb, mrb_value mod)
{
  mrb_int shadertype, precisiontype;
  GLint range[2];
  GLint precision;
  mrb_value range_arr;

  mrb_get_args(mrb, "ii", &shadertype, &precisiontype);
  glGetShaderPrecisionFormat((GLenum) shadertype, (GLenum) precisiontype,
                             range, &precision);

  range_arr = mrb_ary_newv(mrb, 2,
                           mrb_fixnum_value(range[0]),
                           mrb_fixnum_value(range[1]));
  return mrb_ary_newv(mrb, 2, range_arr, mrb_fixnum_value(precision));
}

static mrb_value
mrb_gl_get_shader_source(mrb_state* mrb, mrb_value mod)
{
  mrb_int shader, bufsize;
  GLsizei length;
  GLchar* source_ptr;
  mrb_value source;

  mrb_get_args(mrb, "ii", &shader, &bufsize);
  source_ptr = allocate_char_buffer(mrb, bufsize);

  glGetShaderSource((GLuint) shader, (GLsizei) bufsize,
                    &length, source_ptr);

  source = mrb_str_new(mrb, source_ptr, length);
  release_buffer(mrb, source_ptr);

  return mrb_ary_newv(mrb, 2,
                      mrb_fixnum_value(length),
                      source);
}

static mrb_value
mrb_gl_get_string(mrb_state* mrb, mrb_value mod)
{
  mrb_int name;

  mrb_get_args(mrb, "i", &name);

  return mrb_str_new_cstr(mrb, (const char*) glGetString((GLenum) name));
}

static mrb_value
mrb_gl_get_tex_parameterfv(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname;
  GLfloat params;

  mrb_get_args(mrb, "ii", &target, &pname);
  glGetTexParameterfv((GLenum) target, (GLenum) pname, &params);

  return mrb_float_value(mrb, params);
}

static mrb_value
mrb_gl_get_tex_parameteriv(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname;
  GLint params;

  mrb_get_args(mrb, "ii", &target, &pname);
  glGetTexParameteriv((GLenum) target, (GLenum) pname, &params);

  return mrb_fixnum_value(params);
}

static mrb_value
mrb_gl_get_uniformfv(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, location;
  /* Notice that although the OpenGL ES API only requires 2 arguments here,
   * 3 are needed here since we do not know how many parameters will be
   * returned here. This must be specified by the programmer.
   */
  mrb_int num_args;
  GLfloat* params_ptr;
  mrb_value params;

  mrb_get_args(mrb, "iii", &program, &location, &num_args);
  params_ptr = allocate_float_buffer(mrb, num_args);

  glGetUniformfv((GLuint) program, (GLint) location, params_ptr);

  params = float_buffer_to_mrb_array(mrb, params_ptr, num_args);
  release_buffer(mrb, params_ptr);

  return params;
}

static mrb_value
mrb_gl_get_uniformiv(mrb_state* mrb, mrb_value mod)
{
  mrb_int program, location;
  /* Same as mrb_gl_get_uniformfv, an additional argument is needed
   * for the returned argument array length.
   */
  mrb_int num_args;
  GLint* params_ptr;
  mrb_value params;

  mrb_get_args(mrb, "iii", &program, &location, &num_args);
  params_ptr = allocate_int_buffer(mrb, num_args);

  glGetUniformiv((GLuint) program, (GLint) location, params_ptr);

  params = int_buffer_to_mrb_array(mrb, params_ptr, num_args);
  release_buffer(mrb, params_ptr);

  return params;
}

static mrb_value
mrb_gl_get_uniform_location(mrb_state* mrb, mrb_value mod)
{
  mrb_int program;
  char* name;

  mrb_get_args(mrb, "iz", &program, &name);
  return mrb_fixnum_value(glGetUniformLocation(
      (GLuint) program, (const GLchar*) name));
}

static mrb_value
mrb_gl_get_vertex_attribfv(mrb_state* mrb, mrb_value mod)
{
  mrb_int index, pname;
  int params_len;
  GLfloat* params_ptr;
  mrb_value params;

  mrb_get_args(mrb, "ii", &index, &pname);
  params_len = gl_get_vertex_attrib_number((GLenum) pname);
  params_ptr = allocate_float_buffer(mrb, params_len);

  glGetVertexAttribfv((GLuint) index, (GLenum) pname, params_ptr);

  params = float_buffer_to_mrb_array(mrb, params_ptr, params_len);
  release_buffer(mrb, params_ptr);

  return params;
}

static mrb_value
mrb_gl_get_vertex_attribiv(mrb_state* mrb, mrb_value mod)
{
  mrb_int index, pname;
  int params_len;
  GLint* params_ptr;
  mrb_value params;

  mrb_get_args(mrb, "ii", &index, &pname);
  params_len = gl_get_vertex_attrib_number((GLenum) pname);
  params_ptr = allocate_int_buffer(mrb, params_len);

  glGetVertexAttribiv((GLuint) index, (GLenum) pname, params_ptr);

  params = int_buffer_to_mrb_array(mrb, params_ptr, params_len);
  release_buffer(mrb, params_ptr);

  return params;
}

static mrb_value
mrb_gl_get_vertex_attrib_pointerv(mrb_state* mrb, mrb_value mod)
{
  mrb_int index, pname;
  GLvoid* pointer_ptr = NULL;

  mrb_get_args(mrb, "ii", &index, &pname);
  glGetVertexAttribPointerv((GLuint) index, (GLenum) pname, &pointer_ptr);

  return mrb_str_new_cstr(mrb, (const char*) pointer_ptr);
}

static mrb_value
mrb_gl_hint(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, mode;

  mrb_get_args(mrb, "ii", &target, &mode);
  glHint((GLenum) target, (GLenum) mode);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_is_buffer(mrb_state* mrb, mrb_value mod)
{
  mrb_int buffer;

  mrb_get_args(mrb, "i", &buffer);

  return GL_BOOLEAN_TO_MRB_VALUE(glIsBuffer((GLuint) buffer));
}

static mrb_value
mrb_gl_is_enabled(mrb_state* mrb, mrb_value mod)
{
  mrb_int cap;

  mrb_get_args(mrb, "i", &cap);

  return GL_BOOLEAN_TO_MRB_VALUE(glIsEnabled((GLenum) cap));
}

static mrb_value
mrb_gl_is_framebuffer(mrb_state* mrb, mrb_value mod)
{
  mrb_int framebuffer;

  mrb_get_args(mrb, "i", &framebuffer);

  return GL_BOOLEAN_TO_MRB_VALUE(glIsFramebuffer((GLuint) framebuffer));
}

static mrb_value
mrb_gl_is_program(mrb_state* mrb, mrb_value mod)
{
  mrb_int program;

  mrb_get_args(mrb, "i", &program);

  return GL_BOOLEAN_TO_MRB_VALUE(glIsProgram((GLuint) program));
}

static mrb_value
mrb_gl_is_renderbuffer(mrb_state* mrb, mrb_value mod)
{
  mrb_int renderbuffer;

  mrb_get_args(mrb, "i", &renderbuffer);

  return GL_BOOLEAN_TO_MRB_VALUE(glIsRenderbuffer((GLuint) renderbuffer));
}

static mrb_value
mrb_gl_is_shader(mrb_state* mrb, mrb_value mod)
{
  mrb_int shader;

  mrb_get_args(mrb, "i", &shader);

  return GL_BOOLEAN_TO_MRB_VALUE(glIsShader((GLuint) shader));
}

static mrb_value
mrb_gl_is_texture(mrb_state* mrb, mrb_value mod)
{
  mrb_int texture;

  mrb_get_args(mrb, "i", &texture);

  return GL_BOOLEAN_TO_MRB_VALUE(glIsTexture((GLuint) texture));
}

static mrb_value
mrb_gl_line_width(mrb_state* mrb, mrb_value mod)
{
  mrb_float width;

  mrb_get_args(mrb, "f", &width);
  glLineWidth((GLfloat) width);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_link_program(mrb_state* mrb, mrb_value mod)
{
  mrb_int program;

  mrb_get_args(mrb, "i", &program);
  glLinkProgram((GLuint) program);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_pixel_storei(mrb_state* mrb, mrb_value mod)
{
  mrb_int pname, param;

  mrb_get_args(mrb, "ii", &pname, &param);
  glPixelStorei((GLenum) pname, (GLint) param);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_polygon_offset(mrb_state* mrb, mrb_value mod)
{
  mrb_float factor, units;

  mrb_get_args(mrb, "ff", &factor, &units);
  glPolygonOffset((GLfloat) factor, (GLfloat) units);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_read_pixels(mrb_state* mrb, mrb_value mod)
{
  mrb_int x, y, width, height, format, type;
  GLvoid* pixels = NULL;

  mrb_get_args(mrb, "iiiiii", &x, &y, &width, &height, &format, &type);
  glReadPixels((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height,
               (GLenum) format, (GLenum) type, &pixels);

  return mrb_str_new_cstr(mrb, (const char*) pixels);
}

static mrb_value
mrb_gl_release_shader_compiler(mrb_state* mrb, mrb_value mod)
{
  glReleaseShaderCompiler();

  return mrb_nil_value();
}

static mrb_value
mrb_gl_renderbuffer_storage(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, internalformat, width, height;

  mrb_get_args(mrb, "iiii", &target, &internalformat, &width, &height);
  glRenderbufferStorage((GLenum) target, (GLenum) internalformat,
                        (GLsizei) width, (GLsizei) height);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_sample_coverage(mrb_state* mrb, mrb_value mod)
{
  mrb_float value;
  mrb_value invert;

  mrb_get_args(mrb, "fo", &value, &invert);
  glSampleCoverage((GLclampf) value, MRB_VALUE_TO_GL_BOOLEAN(invert));

  return mrb_nil_value();
}

static mrb_value
mrb_gl_scissor(mrb_state* mrb, mrb_value mod)
{
  mrb_int x, y, width, height;

  mrb_get_args(mrb, "iiii", &x, &y, &width, &height);
  glScissor((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_shader_binary(mrb_state* mrb, mrb_value mod)
{
  mrb_int n, binaryformat, length;
  mrb_value shaders;
  GLuint* shaders_ptr;
  char* binary;
  int binary_len;

  mrb_get_args(mrb, "iAisi", &n, &shaders, &binaryformat,
               &binary, &binary_len, &length);
  shaders_ptr = mrb_array_to_uint_buffer(mrb, shaders);

  glShaderBinary((GLsizei) n, shaders_ptr, (GLenum) binaryformat,
                 (const GLvoid*) binary, (GLsizei) length);
  release_buffer(mrb, shaders_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_shader_source(mrb_state* mrb, mrb_value mod)
{
  mrb_int shader, count;
  GLchar** string_ptr;
  mrb_value string;
  GLint* length_ptr;
  mrb_value length;

  mrb_get_args(mrb, "iiAA", &shader, &count, &string, &length);
  string_ptr = mrb_array_to_char_p_buffer(mrb, string);
  length_ptr = mrb_array_to_int_buffer(mrb, length);

  glShaderSource((GLuint) shader, (GLsizei) count,
                 (const GLchar**) string_ptr, length_ptr);
  release_buffer(mrb, string_ptr);
  release_buffer(mrb, length_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_stencil_func(mrb_state* mrb, mrb_value mod)
{
  mrb_int func, ref, mask;

  mrb_get_args(mrb, "iii", &func, &ref, &mask);
  glStencilFunc((GLenum) func, (GLint) ref, (GLuint) mask);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_stencil_func_separate(mrb_state* mrb, mrb_value mod)
{
  mrb_int face, func, ref, mask;

  mrb_get_args(mrb, "iiii", &face, &func, &ref, &mask);
  glStencilFuncSeparate((GLenum) face, (GLenum) func,
                        (GLint) ref, (GLuint) mask);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_stencil_mask(mrb_state* mrb, mrb_value mod)
{
  mrb_int mask;

  mrb_get_args(mrb, "i", &mask);
  glStencilMask((GLuint) mask);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_stencil_mask_separate(mrb_state* mrb, mrb_value mod)
{
  mrb_int face, mask;

  mrb_get_args(mrb, "ii", &face, &mask);
  glStencilMaskSeparate((GLenum) face, (GLuint) mask);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_stencil_op(mrb_state* mrb, mrb_value mod)
{
  mrb_int fail, zfail, zpass;

  mrb_get_args(mrb, "iii", &fail, &zfail, &zpass);
  glStencilOp((GLenum) fail, (GLenum) zfail, (GLenum) zpass);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_stencil_op_separate(mrb_state* mrb, mrb_value mod)
{
  mrb_int face, fail, zfail, zpass;

  mrb_get_args(mrb, "iiii", &face, &fail, &zfail, &zpass);
  glStencilOpSeparate((GLenum) face, (GLenum) fail,
                      (GLenum) zfail, (GLenum) zpass);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_tex_image_2d(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, level, internalformat, width, height, border, format, type;
  char* pixels;
  int pixels_length;

  mrb_get_args(mrb, "iiiiiiiis", &target, &level, &internalformat, &width,
               &height, &border, &format, &type, &pixels, &pixels_length);
  glTexImage2D((GLenum) target, (GLint) level, (GLint) internalformat,
               (GLsizei) width, (GLsizei) height, (GLint) border,
               (GLenum) format, (GLenum) type, (const GLvoid*) pixels);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_tex_parameterf(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname;
  mrb_float param;

  mrb_get_args(mrb, "iif", &target, &pname, &param);
  glTexParameterf((GLenum) target, (GLenum) pname, (GLfloat) param);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_tex_parameterfv(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname;
  mrb_value params;
  GLfloat* params_ptr;

  mrb_get_args(mrb, "iiA", &target, &pname, &params);
  params_ptr = mrb_array_to_float_buffer(mrb, params);

  glTexParameterfv((GLenum) target, (GLenum) pname, params_ptr);
  release_buffer(mrb, params_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_tex_parameteri(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname, param;

  mrb_get_args(mrb, "iii", &target, &pname, &param);
  glTexParameteri((GLenum) target, (GLenum) pname, (GLint) param);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_tex_parameteriv(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, pname;
  mrb_value params;
  GLint* params_ptr;

  mrb_get_args(mrb, "iiA", &target, &pname, &params);
  params_ptr = mrb_array_to_int_buffer(mrb, params);

  glTexParameteriv((GLenum) target, (GLenum) pname, params_ptr);
  release_buffer(mrb, params_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_tex_sub_image_2d(mrb_state* mrb, mrb_value mod)
{
  mrb_int target, level, xoffset, yoffset, width, height, format, type;
  char* pixels;
  int pixels_len;

  mrb_get_args(mrb, "iiiiiiiis", &target, &level, &xoffset, &yoffset,
               &width, &height, &format, &type, &pixels, &pixels_len);
  glTexSubImage2D((GLenum) target, (GLint) level, (GLint) xoffset,
                  (GLint) yoffset, (GLsizei) width, (GLsizei) height,
                  (GLenum) format, (GLenum) type, (const GLvoid*) pixels);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform1f(mrb_state* mrb, mrb_value mod)
{
  mrb_int location;
  mrb_float x;

  mrb_get_args(mrb, "if", &location, &x);
  glUniform1f((GLint) location, (GLfloat) x);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform1fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLfloat* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_float_buffer(mrb, v);

  glUniform1fv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform1i(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, x;

  mrb_get_args(mrb, "ii", &location, &x);
  glUniform1i((GLint) location, (GLint) x);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform1iv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLint* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_int_buffer(mrb, v);

  glUniform1iv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform2f(mrb_state* mrb, mrb_value mod)
{
  mrb_int location;
  mrb_float x, y;

  mrb_get_args(mrb, "iff", &location, &x, &y);
  glUniform2f((GLint) location, (GLfloat) x, (GLfloat) y);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform2fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLfloat* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_float_buffer(mrb, v);

  glUniform2fv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform2i(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, x, y;

  mrb_get_args(mrb, "iii", &location, &x, &y);
  glUniform2i((GLint) location, (GLint) x, (GLint) y);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform2iv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLint* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_int_buffer(mrb, v);

  glUniform2iv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform3f(mrb_state* mrb, mrb_value mod)
{
  mrb_int location;
  mrb_float x, y, z;

  mrb_get_args(mrb, "ifff", &location, &x, &y, &z);
  glUniform3f((GLint) location, (GLfloat) x, (GLfloat) y, (GLfloat) z);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform3fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLfloat* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_float_buffer(mrb, v);

  glUniform3fv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform3i(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, x, y, z;

  mrb_get_args(mrb, "iiii", &location, &x, &y, &z);
  glUniform3i((GLint) location, (GLint) x, (GLint) y, (GLint) z);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform3iv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLint* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_int_buffer(mrb, v);

  glUniform3iv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform4f(mrb_state* mrb, mrb_value mod)
{
  mrb_int location;
  mrb_float x, y, z, w;

  mrb_get_args(mrb, "iffff", &location, &x, &y, &z, &w);
  glUniform4f((GLint) location, (GLfloat) x, (GLfloat) y,
              (GLfloat) z, (GLfloat) w);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform4fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLfloat* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_float_buffer(mrb, v);

  glUniform4fv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform4i(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, x, y, z, w;

  mrb_get_args(mrb, "iiiii", &location, &x, &y, &z, &w);
  glUniform4i((GLint) location, (GLint) x, (GLint) y, (GLint) z, (GLint) w);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform4iv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  GLint* v_ptr;
  mrb_value v;

  mrb_get_args(mrb, "iiA", &location, &count, &v);
  v_ptr = mrb_array_to_int_buffer(mrb, v);

  glUniform4iv((GLint) location, (GLsizei) count, v_ptr);
  release_buffer(mrb, v_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform_matrix2fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  mrb_value transpose;
  GLfloat* value_ptr;
  mrb_value value;

  mrb_get_args(mrb, "iioA", &location, &count, &transpose, &value);
  value_ptr = mrb_array_to_float_buffer(mrb, value);

  glUniformMatrix2fv((GLint) location, (GLsizei) count,
                     MRB_VALUE_TO_GL_BOOLEAN(transpose),
                     value_ptr);
  release_buffer(mrb, value_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform_matrix3fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  mrb_value transpose;
  GLfloat* value_ptr;
  mrb_value value;

  mrb_get_args(mrb, "iioA", &location, &count, &transpose, &value);
  value_ptr = mrb_array_to_float_buffer(mrb, value);

  glUniformMatrix3fv((GLint) location, (GLsizei) count,
                     MRB_VALUE_TO_GL_BOOLEAN(transpose),
                     value_ptr);
  release_buffer(mrb, value_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_uniform_matrix4fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int location, count;
  mrb_value transpose;
  GLfloat* value_ptr;
  mrb_value value;

  mrb_get_args(mrb, "iioA", &location, &count, &transpose, &value);
  value_ptr = mrb_array_to_float_buffer(mrb, value);

  glUniformMatrix4fv((GLint) location, (GLsizei) count,
                     MRB_VALUE_TO_GL_BOOLEAN(transpose),
                     value_ptr);
  release_buffer(mrb, value_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_use_program(mrb_state* mrb, mrb_value mod)
{
  mrb_int program;

  mrb_get_args(mrb, "i", &program);
  glUseProgram((GLuint) program);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_validate_program(mrb_state* mrb, mrb_value mod)
{
  mrb_int program;

  mrb_get_args(mrb, "i", &program);
  glValidateProgram((GLuint) program);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib1f(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  mrb_float x;

  mrb_get_args(mrb, "if", &indx, &x);
  glVertexAttrib1f((GLuint) indx, (GLfloat) x);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib1fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  GLfloat* values_ptr;
  mrb_value values;

  mrb_get_args(mrb, "iA", &indx, &values);
  values_ptr = mrb_array_to_float_buffer(mrb, values);

  glVertexAttrib1fv((GLuint) indx, values_ptr);
  release_buffer(mrb, values_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib2f(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  mrb_float x, y;

  mrb_get_args(mrb, "iff", &indx, &x, &y);
  glVertexAttrib2f((GLuint) indx, (GLfloat) x, (GLfloat) y);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib2fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  GLfloat* values_ptr;
  mrb_value values;

  mrb_get_args(mrb, "iA", &indx, &values);
  values_ptr = mrb_array_to_float_buffer(mrb, values);

  glVertexAttrib2fv((GLuint) indx, values_ptr);
  release_buffer(mrb, values_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib3f(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  mrb_float x, y, z;

  mrb_get_args(mrb, "ifff", &indx, &x, &y, &z);
  glVertexAttrib3f((GLuint) indx, (GLfloat) x, (GLfloat) y, (GLfloat) z);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib3fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  GLfloat* values_ptr;
  mrb_value values;

  mrb_get_args(mrb, "iA", &indx, &values);
  values_ptr = mrb_array_to_float_buffer(mrb, values);

  glVertexAttrib3fv((GLuint) indx, values_ptr);
  release_buffer(mrb, values_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib4f(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  mrb_float x, y, z, w;

  mrb_get_args(mrb, "iffff", &indx, &x, &y, &z, &w);
  glVertexAttrib4f((GLuint) indx, (GLfloat) x, (GLfloat) y,
                   (GLfloat) z, (GLfloat) w);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib4fv(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx;
  GLfloat* values_ptr;
  mrb_value values;

  mrb_get_args(mrb, "iA", &indx, &values);
  values_ptr = mrb_array_to_float_buffer(mrb, values);

  glVertexAttrib4fv((GLuint) indx, values_ptr);
  release_buffer(mrb, values_ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_vertex_attrib_pointer(mrb_state* mrb, mrb_value mod)
{
  mrb_int indx, size, type, stride;
  mrb_value normalized;
  char* ptr;
  int ptr_len;

  mrb_get_args(mrb, "iiiois", &indx, &size, &type, &normalized,
               &stride, &ptr, &ptr_len);
  glVertexAttribPointer((GLuint) indx, (GLint) size, (GLenum) type,
                        MRB_VALUE_TO_GL_BOOLEAN(normalized),
                        (GLsizei) stride, (const GLvoid*) ptr);

  return mrb_nil_value();
}

static mrb_value
mrb_gl_viewport(mrb_state* mrb, mrb_value mod)
{
  mrb_int x, y, width, height;

  mrb_get_args(mrb, "iiii", &x, &y, &width, &height);
  glViewport((GLint) x, (GLint) y, (GLsizei) width, (GLsizei) height);

  return mrb_nil_value();
}

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
#ifdef GL_STENCIL_INDEX
  mrb_define_const(mrb, mod_gl2, "GL_STENCIL_INDEX", mrb_fixnum_value(GL_STENCIL_INDEX));
#endif
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
  mrb_define_module_function(mrb, mod_gl2, "glActiveTexture", mrb_gl_active_texture, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glAttachShader", mrb_gl_attach_shader, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glBindAttribLocation", mrb_gl_bind_attrib_location, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glBindBuffer", mrb_gl_bind_buffer, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glBindFramebuffer", mrb_gl_bind_framebuffer, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glBindRenderbuffer", mrb_gl_bind_renderbuffer, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glBindTexture", mrb_gl_bind_texture, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glBlendColor", mrb_gl_blend_color, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glBlendEquation", mrb_gl_blend_equation, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glBlendEquationSeparate", mrb_gl_blend_equation_separate, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glBlendFunc", mrb_gl_blend_func, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glBlendFuncSeparate", mrb_gl_blend_func_separate, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glBufferData", mrb_gl_buffer_data, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glBufferSubData", mrb_gl_buffer_sub_data, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glCheckFramebufferStatus", mrb_gl_check_framebuffer_status, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glClear", mrb_gl_clear, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glClearColor", mrb_gl_clear_color, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glClearDepthf", mrb_gl_clear_depthf, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glClearStencil", mrb_gl_clear_stencil, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glColorMask", mrb_gl_color_mask, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glCompileShader", mrb_gl_compile_shader, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glCompressedTexImage2D", mrb_gl_compressed_tex_image_2d, ARGS_REQ(8));
  mrb_define_module_function(mrb, mod_gl2, "glCompressedTexSubImage2D", mrb_gl_compressed_tex_sub_image_2d, ARGS_REQ(9));
  mrb_define_module_function(mrb, mod_gl2, "glCopyTexImage2D", mrb_gl_copy_tex_image_2d, ARGS_REQ(8));
  mrb_define_module_function(mrb, mod_gl2, "glCopyTexSubImage2D", mrb_gl_copy_tex_sub_image_2d, ARGS_REQ(8));
  mrb_define_module_function(mrb, mod_gl2, "glCreateProgram", mrb_gl_create_program, ARGS_NONE());
  mrb_define_module_function(mrb, mod_gl2, "glCreateShader", mrb_gl_create_shader, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glCullFace", mrb_gl_cull_face, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glDeleteBuffers", mrb_gl_delete_buffers, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glDeleteFramebuffers", mrb_gl_delete_framebuffers, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glDeleteProgram", mrb_gl_delete_program, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glDeleteRenderbuffers", mrb_gl_delete_renderbuffers, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glDeleteShader", mrb_gl_delete_shader, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glDeleteTextures", mrb_gl_delete_textures, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glDepthFunc", mrb_gl_depth_func, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glDepthMask", mrb_gl_depth_mask, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glDepthRangef", mrb_gl_depth_rangef, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glDetachShader", mrb_gl_detach_shader, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glDisable", mrb_gl_disable, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glDisableVertexAttribArray", mrb_gl_disable_vertex_attrib_array, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glDrawArrays", mrb_gl_draw_arrays, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glDrawElements", mrb_gl_draw_elements, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glEnable", mrb_gl_enable, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glEnableVertexAttribArray", mrb_gl_enable_vertex_attrib_array, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glFinish", mrb_gl_finish, ARGS_NONE());
  mrb_define_module_function(mrb, mod_gl2, "glFlush", mrb_gl_flush, ARGS_NONE());
  mrb_define_module_function(mrb, mod_gl2, "glFramebufferRenderbuffer", mrb_gl_framebuffer_renderbuffer, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glFramebufferTexture2D", mrb_gl_framebuffer_texture_2d, ARGS_REQ(5));
  mrb_define_module_function(mrb, mod_gl2, "glFrontFace", mrb_gl_front_face, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGenBuffers", mrb_gl_gen_buffers, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGenerateMipmap", mrb_gl_generate_mipmap, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGenFramebuffers", mrb_gl_gen_framebuffers, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGenRenderbuffers", mrb_gl_gen_renderbuffers, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGenTextures", mrb_gl_gen_textures, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGetActiveAttrib", mrb_gl_get_active_attrib, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glGetActiveUniform", mrb_gl_get_active_uniform, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glGetAttachedShaders", mrb_gl_get_attached_shaders, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetAttribLocation", mrb_gl_get_attrib_location, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetBooleanv", mrb_gl_get_booleanv, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGetBufferParameteriv", mrb_gl_get_buffer_parameteriv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetError", mrb_gl_get_error, ARGS_NONE());
  mrb_define_module_function(mrb, mod_gl2, "glGetFloatv", mrb_gl_get_floatv, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGetFramebufferAttachmentParameteriv", mrb_gl_get_framebuffer_attachment_parameteriv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glGetIntegerv", mrb_gl_get_integerv, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGetProgramiv", mrb_gl_get_programiv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetProgramInfoLog", mrb_gl_get_program_info_log, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetRenderbufferParameteriv", mrb_gl_get_renderbuffer_parameteriv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetShaderiv", mrb_gl_get_shaderiv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetShaderInfoLog", mrb_gl_get_shader_info_log, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetShaderPrecisionFormat", mrb_gl_get_shader_precision_format, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetShaderSource", mrb_gl_get_shader_source, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetString", mrb_gl_get_string, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glGetTexParameterfv", mrb_gl_get_tex_parameterfv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetTexParameteriv", mrb_gl_get_tex_parameteriv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetUniformfv", mrb_gl_get_uniformfv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetUniformiv", mrb_gl_get_uniformiv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetUniformLocation", mrb_gl_get_uniform_location, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetVertexAttribfv", mrb_gl_get_vertex_attribfv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetVertexAttribiv", mrb_gl_get_vertex_attribiv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glGetVertexAttribPointerv", mrb_gl_get_vertex_attrib_pointerv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glHint", mrb_gl_hint, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glIsBuffer", mrb_gl_is_buffer, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glIsEnabled", mrb_gl_is_enabled, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glIsFramebuffer", mrb_gl_is_framebuffer, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glIsProgram", mrb_gl_is_program, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glIsRenderbuffer", mrb_gl_is_renderbuffer, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glIsShader", mrb_gl_is_shader, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glIsTexture", mrb_gl_is_texture, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glLineWidth", mrb_gl_line_width, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glLinkProgram", mrb_gl_link_program, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glPixelStorei", mrb_gl_pixel_storei, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glPolygonOffset", mrb_gl_polygon_offset, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glReadPixels", mrb_gl_read_pixels, ARGS_REQ(6));
  mrb_define_module_function(mrb, mod_gl2, "glReleaseShaderCompiler", mrb_gl_release_shader_compiler, ARGS_NONE());
  mrb_define_module_function(mrb, mod_gl2, "glRenderbufferStorage", mrb_gl_renderbuffer_storage, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glSampleCoverage", mrb_gl_sample_coverage, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glScissor", mrb_gl_scissor, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glShaderBinary", mrb_gl_shader_binary, ARGS_REQ(5));
  mrb_define_module_function(mrb, mod_gl2, "glShaderSource", mrb_gl_shader_source, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glStencilFunc", mrb_gl_stencil_func, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glStencilFuncSeparate", mrb_gl_stencil_func_separate, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glStencilMask", mrb_gl_stencil_mask, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glStencilMaskSeparate", mrb_gl_stencil_mask_separate, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glStencilOp", mrb_gl_stencil_op, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glStencilOpSeparate", mrb_gl_stencil_op_separate, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glTexImage2D", mrb_gl_tex_image_2d, ARGS_REQ(9));
  mrb_define_module_function(mrb, mod_gl2, "glTexParameterf", mrb_gl_tex_parameterf, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glTexParameterfv", mrb_gl_tex_parameterfv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glTexParameteri", mrb_gl_tex_parameteri, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glTexParameteriv", mrb_gl_tex_parameteriv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glTexSubImage2D", mrb_gl_tex_sub_image_2d, ARGS_REQ(9));
  mrb_define_module_function(mrb, mod_gl2, "glUniform1f", mrb_gl_uniform1f, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glUniform1fv", mrb_gl_uniform1fv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform1i", mrb_gl_uniform1i, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glUniform1iv", mrb_gl_uniform1iv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform2f", mrb_gl_uniform2f, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform2fv", mrb_gl_uniform2fv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform2i", mrb_gl_uniform2i, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform2iv", mrb_gl_uniform2iv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform3f", mrb_gl_uniform3f, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glUniform3fv", mrb_gl_uniform3fv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform3i", mrb_gl_uniform3i, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glUniform3iv", mrb_gl_uniform3iv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform4f", mrb_gl_uniform4f, ARGS_REQ(5));
  mrb_define_module_function(mrb, mod_gl2, "glUniform4fv", mrb_gl_uniform4fv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniform4i", mrb_gl_uniform4i, ARGS_REQ(5));
  mrb_define_module_function(mrb, mod_gl2, "glUniform4iv", mrb_gl_uniform4iv, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glUniformMatrix2fv", mrb_gl_uniform_matrix2fv, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glUniformMatrix3fv", mrb_gl_uniform_matrix3fv, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glUniformMatrix4fv", mrb_gl_uniform_matrix4fv, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glUseProgram", mrb_gl_use_program, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glValidateProgram", mrb_gl_validate_program, ARGS_REQ(1));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib1f", mrb_gl_vertex_attrib1f, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib1fv", mrb_gl_vertex_attrib1fv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib2f", mrb_gl_vertex_attrib2f, ARGS_REQ(3));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib2fv", mrb_gl_vertex_attrib2fv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib3f", mrb_gl_vertex_attrib3f, ARGS_REQ(4));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib3fv", mrb_gl_vertex_attrib3fv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib4f", mrb_gl_vertex_attrib4f, ARGS_REQ(5));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttrib4fv", mrb_gl_vertex_attrib4fv, ARGS_REQ(2));
  mrb_define_module_function(mrb, mod_gl2, "glVertexAttribPointer", mrb_gl_vertex_attrib_pointer, ARGS_REQ(6));
  mrb_define_module_function(mrb, mod_gl2, "glViewport", mrb_gl_viewport, ARGS_REQ(4));
}
