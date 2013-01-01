/* Helper macros for defining functions */
#ifndef _mrb_gl_defs_h_
#define _mrb_gl_defs_h_

#define MRB_ATTACH_CONST(name_) \
  mrb_define_const(mrb, mod_gl2, "GL_" #name_, mrb_fixnum_value(GL_##name_))

#define MRB_ATTACH_FUNC(name_, num_) \
  mrb_define_module_function(mrb, mod_gl2, "gl" #name_, mrb_gl_##name_, ARGS_REQ(num_))

/* '*' is not allowed in macro name, so we have to use this fix */
#define GLenum_v(x_) (GLenum) x_
#define GLuint_v(x_) (GLuint) x_
#define GLsizeiptr_v(x_) (GLsizeiptr) x_
#define GLvoid_p_v(x_) (GLvoid*) x_
#define GLchar_p_v(x_) (GLchar*) x_
#define GLclampf_v(x_) (GLclampf) x_
#define GLintptr_v(x_) (GLintptr) x_
#define GLbitfield_v(x_) (GLbitfield) x_
#define GLint_v(x_) (GLint) x_
#define GLboolean_v(x_) (mrb_test(x_) ? (GL_TRUE) : (GL_FALSE))

/* OpenGL types => mruby types */
#define MRB_TYPE_GLenum mrb_int
#define MRB_TYPE_GLuint mrb_int
#define MRB_TYPE_GLsizeiptr mrb_int
#define MRB_TYPE_GLvoid_p char*
#define MRB_TYPE_GLchar_p char*
#define MRB_TYPE_GLclampf mrb_float
#define MRB_TYPE_GLintptr mrb_int
#define MRB_TYPE_GLbitfield mrb_int
#define MRB_TYPE_GLint mrb_int
#define MRB_TYPE_GLboolean mrb_value

#define MRB_SPEC_GLenum "i"
#define MRB_SPEC_GLuint "i"
#define MRB_SPEC_GLsizeiptr "i"
#define MRB_SPEC_GLvoid_p "z"
#define MRB_SPEC_GLchar_p "z"
#define MRB_SPEC_GLclampf "f"
#define MRB_SPEC_GLintptr "i"
#define MRB_SPEC_GLbitfield "i"
#define MRB_SPEC_GLint "i"
#define MRB_SPEC_GLboolean "o"

#define RET_CONVERT_GLenum(x_) mrb_fixnum_value(x_)

#define ARG_DEF_SINGLE(t_, n_) \
  MRB_TYPE_##t_ n_
#define ARG_DEF_1(t1_) \
  ARG_DEF_SINGLE(t1_, arg1)
#define ARG_DEF_2(t1_, t2_) \
  ARG_DEF_1(t1_); ARG_DEF_SINGLE(t2_, arg2)
#define ARG_DEF_3(t1_, t2_, t3_) \
  ARG_DEF_2(t1_, t2_); ARG_DEF_SINGLE(t3_, arg3)
#define ARG_DEF_4(t1_, t2_, t3_, t4_) \
  ARG_DEF_3(t1_, t2_, t3_); ARG_DEF_SINGLE(t4_, arg4)
#define ARG_DEF_5(t1_, t2_, t3_, t4_, t5_) \
  ARG_DEF_4(t1_, t2_, t3_, t4_); ARG_DEF_SINGLE(t5_, arg5)
#define ARG_DEF_6(t1_, t2_, t3_, t4_, t5_, t6_) \
  ARG_DEF_5(t1_, t2_, t3_, t4_, t5_); ARG_DEF_SINGLE(t6_, arg6)
#define ARG_DEF_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_) \
  ARG_DEF_6(t1_, t2_, t3_, t4_, t5_, t6_); ARG_DEF_SINGLE(t7_, arg7)
#define ARG_DEF_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_) \
  ARG_DEF_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_); ARG_DEF_SINGLE(t8_, arg8)
#define ARG_DEF_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_) \
  ARG_DEF_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_); ARG_DEF_SINGLE(t9_, arg9)
#define ARG_DEF_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_) \
  ARG_DEF_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_); ARG_DEF_SINGLE(t10_, arg10)

#define ARG_SPEC_SINGLE(t_) \
  MRB_SPEC_##t_
#define ARG_SPEC_1(t1_) \
  ARG_SPEC_SINGLE(t1_)
#define ARG_SPEC_2(t1_, t2_) \
  ARG_SPEC_1(t1_) ARG_SPEC_SINGLE(t2_)
#define ARG_SPEC_3(t1_, t2_, t3_) \
  ARG_SPEC_2(t1_, t2_) ARG_SPEC_SINGLE(t3_)
#define ARG_SPEC_4(t1_, t2_, t3_, t4_) \
  ARG_SPEC_3(t1_, t2_, t3_) ARG_SPEC_SINGLE(t4_)
#define ARG_SPEC_5(t1_, t2_, t3_, t4_, t5_) \
  ARG_SPEC_4(t1_, t2_, t3_, t4_) ARG_SPEC_SINGLE(t5_)
#define ARG_SPEC_6(t1_, t2_, t3_, t4_, t5_, t6_) \
  ARG_SPEC_5(t1_, t2_, t3_, t4_, t5_) ARG_SPEC_SINGLE(t6_)
#define ARG_SPEC_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_) \
  ARG_SPEC_6(t1_, t2_, t3_, t4_, t5_, t6_) ARG_SPEC_SINGLE(t7_)
#define ARG_SPEC_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_) \
  ARG_SPEC_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_) ARG_SPEC_SINGLE(t8_)
#define ARG_SPEC_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_) \
  ARG_SPEC_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_) ARG_SPEC_SINGLE(t9_)
#define ARG_SPEC_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_) \
  ARG_SPEC_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_) ARG_SPEC_SINGLE(t10_)

#define ARG_PTR_1 &arg1
#define ARG_PTR_2 ARG_PTR_1, &arg2
#define ARG_PTR_3 ARG_PTR_2, &arg3
#define ARG_PTR_4 ARG_PTR_3, &arg4
#define ARG_PTR_5 ARG_PTR_4, &arg5
#define ARG_PTR_6 ARG_PTR_5, &arg6
#define ARG_PTR_7 ARG_PTR_6, &arg7
#define ARG_PTR_8 ARG_PTR_7, &arg8
#define ARG_PTR_9 ARG_PTR_8, &arg9
#define ARG_PTR_10 ARG_PTR_9, &arg10

#define ARG_GL_SINGLE(t_, n_) \
  t_##_v(n_)
#define ARG_GL_1(t1_) \
  ARG_GL_SINGLE(t1_, arg1)
#define ARG_GL_2(t1_, t2_) \
  ARG_GL_1(t1_), ARG_GL_SINGLE(t2_, arg2)
#define ARG_GL_3(t1_, t2_, t3_) \
  ARG_GL_2(t1_, t2_), ARG_GL_SINGLE(t3_, arg3)
#define ARG_GL_4(t1_, t2_, t3_, t4_) \
  ARG_GL_3(t1_, t2_, t3_), ARG_GL_SINGLE(t4_, arg4)
#define ARG_GL_5(t1_, t2_, t3_, t4_, t5_) \
  ARG_GL_4(t1_, t2_, t3_, t4_), ARG_GL_SINGLE(t5_, arg5)
#define ARG_GL_6(t1_, t2_, t3_, t4_, t5_, t6_) \
  ARG_GL_5(t1_, t2_, t3_, t4_, t5_), ARG_GL_SINGLE(t6_, arg6)
#define ARG_GL_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_) \
  ARG_GL_6(t1_, t2_, t3_, t4_, t5_, t6_), ARG_GL_SINGLE(t7_, arg7)
#define ARG_GL_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_) \
  ARG_GL_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_), ARG_GL_SINGLE(t8_, arg8)
#define ARG_GL_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_) \
  ARG_GL_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_), ARG_GL_SINGLE(t9_, arg9)
#define ARG_GL_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_) \
  ARG_GL_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_), ARG_GL_SINGLE(t10_, arg10)

#define DEF_NO_RETURN_FUNC(name_, num_, def_args_, spec_args_, ptr_args_, gl_args_) \
  static mrb_value \
  mrb_gl_##name_(mrb_state *mrb, mrb_value self) \
  { \
    def_args_; \
    if (mrb_get_args(mrb, spec_args_, ptr_args_) != num_) { \
      mrb_raise(mrb, E_ARGUMENT_ERROR, "Cannot get enough arguments!"); \
    } \
    gl##name_(gl_args_); \
    return mrb_nil_value(); \
  }

#define DEF_RETURN_FUNC(name_, num_, def_args_, spec_args_, ptr_args_, gl_args_, ret_t_) \
  static mrb_value \
  mrb_gl_##name_(mrb_state *mrb, mrb_value self) \
  { \
    def_args_; \
    if (mrb_get_args(mrb, spec_args_, ptr_args_) != num_) { \
      mrb_raise(mrb, E_ARGUMENT_ERROR, "Cannot get enough arguments!"); \
    } \
    return RET_CONVERT_##ret_t_(gl##name_(gl_args_)); \
  }

#define FUNC_ARG_1(name_, t1_) \
  DEF_NO_RETURN_FUNC(name_, 1, ARG_DEF_1(t1_), \
                     ARG_SPEC_1(t1_), ARG_PTR_1, \
                     ARG_GL_1(t1_))
#define FUNC_ARG_2(name_, t1_, t2_) \
  DEF_NO_RETURN_FUNC(name_, 2, ARG_DEF_2(t1_, t2_), \
                     ARG_SPEC_2(t1_, t2_), ARG_PTR_2, \
                     ARG_GL_2(t1_, t2_))
#define FUNC_ARG_3(name_, t1_, t2_, t3_) \
  DEF_NO_RETURN_FUNC(name_, 3, ARG_DEF_3(t1_, t2_, t3_), \
                     ARG_SPEC_3(t1_, t2_, t3_), ARG_PTR_3, \
                     ARG_GL_3(t1_, t2_, t3_))
#define FUNC_ARG_4(name_, t1_, t2_, t3_, t4_) \
  DEF_NO_RETURN_FUNC(name_, 4, ARG_DEF_4(t1_, t2_, t3_, t4_), \
                     ARG_SPEC_4(t1_, t2_, t3_, t4_), ARG_PTR_4, \
                     ARG_GL_4(t1_, t2_, t3_, t4_))
#define FUNC_ARG_5(name_, t1_, t2_, t3_, t4_, t5_) \
  DEF_NO_RETURN_FUNC(name_, 5, ARG_DEF_5(t1_, t2_, t3_, t4_, t5_), \
                     ARG_SPEC_5(t1_, t2_, t3_, t4_, t5_), ARG_PTR_5, \
                     ARG_GL_5(t1_, t2_, t3_, t4_, t5_))
#define FUNC_ARG_6(name_, t1_, t2_, t3_, t4_, t5_, t6_) \
  DEF_NO_RETURN_FUNC(name_, 6, ARG_DEF_6(t1_, t2_, t3_, t4_, t5_, t6_), \
                     ARG_SPEC_6(t1_, t2_, t3_, t4_, t5_, t6_), ARG_PTR_6, \
                     ARG_GL_6(t1_, t2_, t3_, t4_, t5_, t6_))
#define FUNC_ARG_7(name_, t1_, t2_, t3_, t4_, t5_, t6_, t7_) \
  DEF_NO_RETURN_FUNC(name_, 7, ARG_DEF_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_), \
                     ARG_SPEC_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_), ARG_PTR_7, \
                     ARG_GL_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_))
#define FUNC_ARG_8(name_, t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_) \
  DEF_NO_RETURN_FUNC(name_, 8, ARG_DEF_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_), \
                     ARG_SPEC_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_), ARG_PTR_8, \
                     ARG_GL_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_))
#define FUNC_ARG_9(name_, t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_) \
  DEF_NO_RETURN_FUNC(name_, 9, ARG_DEF_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_), \
                     ARG_SPEC_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_), ARG_PTR_9, \
                     ARG_GL_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_))
#define FUNC_ARG_10(name_, t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_) \
  DEF_NO_RETURN_FUNC(name_, 10, ARG_DEF_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_), \
                     ARG_SPEC_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_), ARG_PTR_10, \
                     ARG_GL_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_))

#define FUNC_RET_ARG_1(name_, ret_t_, t1_)   \
  DEF_RETURN_FUNC(name_, 1, ARG_DEF_1(t1_), \
                  ARG_SPEC_1(t1_), ARG_PTR_1, \
                  ARG_GL_1(t1_), \
                  ret_t_)
#define FUNC_RET_ARG_2(name_, ret_t_, t1_, t2_) \
  DEF_RETURN_FUNC(name_, 2, ARG_DEF_2(t1_, t2_), \
                  ARG_SPEC_2(t1_, t2_), ARG_PTR_2, \
                  ARG_GL_2(t1_, t2_), \
                  ret_t_)
#define FUNC_RET_ARG_3(name_, ret_t_, t1_, t2_, t3_) \
  DEF_RETURN_FUNC(name_, 3, ARG_DEF_3(t1_, t2_, t3_), \
                  ARG_SPEC_3(t1_, t2_, t3_), ARG_PTR_3, \
                  ARG_GL_3(t1_, t2_, t3_), \
                  ret_t_)
#define FUNC_RET_ARG_4(name_, ret_t_, t1_, t2_, t3_, t4_) \
  DEF_RETURN_FUNC(name_, 4, ARG_DEF_4(t1_, t2_, t3_, t4_), \
                  ARG_SPEC_4(t1_, t2_, t3_, t4_), ARG_PTR_4, \
                  ARG_GL_4(t1_, t2_, t3_, t4_), \
                  ret_t_)
#define FUNC_RET_ARG_5(name_, ret_t_, t1_, t2_, t3_, t4_, t5_) \
  DEF_RETURN_FUNC(name_, 5, ARG_DEF_5(t1_, t2_, t3_, t4_, t5_), \
                  ARG_SPEC_5(t1_, t2_, t3_, t4_, t5_), ARG_PTR_5, \
                  ARG_GL_5(t1_, t2_, t3_, t4_, t5_), \
                  ret_t_)
#define FUNC_RET_ARG_6(name_, ret_t_, t1_, t2_, t3_, t4_, t5_, t6_) \
  DEF_RETURN_FUNC(name_, 6, ARG_DEF_6(t1_, t2_, t3_, t4_, t5_, t6_), \
                  ARG_SPEC_6(t1_, t2_, t3_, t4_, t5_, t6_), ARG_PTR_6, \
                  ARG_GL_6(t1_, t2_, t3_, t4_, t5_, t6_), \
                  ret_t_)
#define FUNC_RET_ARG_7(name_, ret_t_, t1_, t2_, t3_, t4_, t5_, t6_, t7_) \
  DEF_RETURN_FUNC(name_, 7, ARG_DEF_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_), \
                  ARG_SPEC_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_), ARG_PTR_7, \
                  ARG_GL_7(t1_, t2_, t3_, t4_, t5_, t6_, t7_), \
                  ret_t_)
#define FUNC_RET_ARG_8(name_, ret_t_, t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_) \
  DEF_RETURN_FUNC(name_, 8, ARG_DEF_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_), \
                  ARG_SPEC_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_), ARG_PTR_8, \
                  ARG_GL_8(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_), \
                  ret_t_)
#define FUNC_RET_ARG_9(name_, ret_t_, t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_) \
  DEF_RETURN_FUNC(name_, 9, ARG_DEF_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_), \
                  ARG_SPEC_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_), ARG_PTR_9, \
                  ARG_GL_9(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_), \
                  ret_t_)
#define FUNC_RET_ARG_10(name_, ret_t_, t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_) \
  DEF_RETURN_FUNC(name_, 10, ARG_DEF_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_), \
                  ARG_SPEC_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_), ARG_PTR_10, \
                  ARG_GL_10(t1_, t2_, t3_, t4_, t5_, t6_, t7_, t8_, t9_, t10_), \
                  ret_t_)

#endif
