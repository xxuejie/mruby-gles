#include <mruby.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

static struct RClass *mod_gl2ext;

void
mrb_mruby_gles_gem_gl2ext_init(mrb_state* mrb)
{
  mod_gl2ext = mrb_define_module(mrb, "GL2Ext");

  /* OES extension tokens */
#ifdef GL_OES_compressed_ETC1_RGB8_texture
  mrb_define_const(mrb, mod_gl2ext, "GL_ETC1_RGB8_OES", mrb_fixnum_value(GL_ETC1_RGB8_OES));
#endif

#ifdef GL_OES_compressed_paletted_texture
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE4_RGB8_OES", mrb_fixnum_value(GL_PALETTE4_RGB8_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE4_RGBA8_OES", mrb_fixnum_value(GL_PALETTE4_RGBA8_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE4_R5_G6_B5_OES", mrb_fixnum_value(GL_PALETTE4_R5_G6_B5_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE4_RGBA4_OES", mrb_fixnum_value(GL_PALETTE4_RGBA4_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE4_RGB5_A1_OES", mrb_fixnum_value(GL_PALETTE4_RGB5_A1_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE8_RGB8_OES", mrb_fixnum_value(GL_PALETTE8_RGB8_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE8_RGBA8_OES", mrb_fixnum_value(GL_PALETTE8_RGBA8_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE8_R5_G6_B5_OES", mrb_fixnum_value(GL_PALETTE8_R5_G6_B5_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE8_RGBA4_OES", mrb_fixnum_value(GL_PALETTE8_RGBA4_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PALETTE8_RGB5_A1_OES", mrb_fixnum_value(GL_PALETTE8_RGB5_A1_OES));
#endif

#ifdef GL_OES_depth24
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_COMPONENT24_OES", mrb_fixnum_value(GL_DEPTH_COMPONENT24_OES));
#endif

#ifdef GL_OES_depth32
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_COMPONENT32_OES", mrb_fixnum_value(GL_DEPTH_COMPONENT32_OES));
#endif

#ifdef GL_OES_element_index_uint
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_INT", mrb_fixnum_value(GL_UNSIGNED_INT));
#endif

#ifdef GL_OES_get_program_binary
  mrb_define_const(mrb, mod_gl2ext, "GL_PROGRAM_BINARY_LENGTH_OES", mrb_fixnum_value(GL_PROGRAM_BINARY_LENGTH_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_NUM_PROGRAM_BINARY_FORMATS_OES", mrb_fixnum_value(GL_NUM_PROGRAM_BINARY_FORMATS_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_PROGRAM_BINARY_FORMATS_OES", mrb_fixnum_value(GL_PROGRAM_BINARY_FORMATS_OES));
#endif

#ifdef GL_OES_mapbuffer
  mrb_define_const(mrb, mod_gl2ext, "GL_WRITE_ONLY_OES", mrb_fixnum_value(GL_WRITE_ONLY_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_BUFFER_ACCESS_OES", mrb_fixnum_value(GL_BUFFER_ACCESS_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_BUFFER_MAPPED_OES", mrb_fixnum_value(GL_BUFFER_MAPPED_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_BUFFER_MAP_POINTER_OES", mrb_fixnum_value(GL_BUFFER_MAP_POINTER_OES));
#endif

#ifdef GL_OES_packed_depth_stencil
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_STENCIL_OES", mrb_fixnum_value(GL_DEPTH_STENCIL_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_INT_24_8_OES", mrb_fixnum_value(GL_UNSIGNED_INT_24_8_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH24_STENCIL8_OES", mrb_fixnum_value(GL_DEPTH24_STENCIL8_OES));
#endif

#ifdef GL_OES_rgb8_rgba8
  mrb_define_const(mrb, mod_gl2ext, "GL_RGB8_OES", mrb_fixnum_value(GL_RGB8_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_RGBA8_OES", mrb_fixnum_value(GL_RGBA8_OES));
#endif

#ifdef GL_OES_standard_derivatives
  mrb_define_const(mrb, mod_gl2ext, "GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES", mrb_fixnum_value(GL_FRAGMENT_SHADER_DERIVATIVE_HINT_OES));
#endif

#ifdef GL_OES_stencil1
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_INDEX1_OES", mrb_fixnum_value(GL_STENCIL_INDEX1_OES));
#endif

#ifdef GL_OES_stencil4
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_INDEX4_OES", mrb_fixnum_value(GL_STENCIL_INDEX4_OES));
#endif

#ifdef GL_OES_texture_3D
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_WRAP_R_OES", mrb_fixnum_value(GL_TEXTURE_WRAP_R_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_3D_OES", mrb_fixnum_value(GL_TEXTURE_3D_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_BINDING_3D_OES", mrb_fixnum_value(GL_TEXTURE_BINDING_3D_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_MAX_3D_TEXTURE_SIZE_OES", mrb_fixnum_value(GL_MAX_3D_TEXTURE_SIZE_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_SAMPLER_3D_OES", mrb_fixnum_value(GL_SAMPLER_3D_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES", mrb_fixnum_value(GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_OES));
#endif

#ifdef GL_OES_texture_half_float
  mrb_define_const(mrb, mod_gl2ext, "GL_HALF_FLOAT_OES", mrb_fixnum_value(GL_HALF_FLOAT_OES));
#endif

#ifdef GL_OES_vertex_array_object
  mrb_define_const(mrb, mod_gl2ext, "GL_VERTEX_ARRAY_BINDING_OES", mrb_fixnum_value(GL_VERTEX_ARRAY_BINDING_OES));
#endif

#ifdef GL_OES_vertex_type_10_10_10_2
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_INT_10_10_10_2_OES", mrb_fixnum_value(GL_UNSIGNED_INT_10_10_10_2_OES));
  mrb_define_const(mrb, mod_gl2ext, "GL_INT_10_10_10_2_OES", mrb_fixnum_value(GL_INT_10_10_10_2_OES));
#endif

#ifdef GL_AMD_compressed_3DC_texture
  mrb_define_const(mrb, mod_gl2ext, "GL_3DC_X_AMD", mrb_fixnum_value(GL_3DC_X_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_3DC_XY_AMD", mrb_fixnum_value(GL_3DC_XY_AMD));
#endif

#ifdef GL_AMD_compressed_ATC_texture
  mrb_define_const(mrb, mod_gl2ext, "GL_ATC_RGB_AMD", mrb_fixnum_value(GL_ATC_RGB_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_ATC_RGBA_EXPLICIT_ALPHA_AMD", mrb_fixnum_value(GL_ATC_RGBA_EXPLICIT_ALPHA_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD", mrb_fixnum_value(GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD));
#endif

#ifdef GL_AMD_performance_monitor
  mrb_define_const(mrb, mod_gl2ext, "GL_COUNTER_TYPE_AMD", mrb_fixnum_value(GL_COUNTER_TYPE_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_COUNTER_RANGE_AMD", mrb_fixnum_value(GL_COUNTER_RANGE_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_INT64_AMD", mrb_fixnum_value(GL_UNSIGNED_INT64_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_PERCENTAGE_AMD", mrb_fixnum_value(GL_PERCENTAGE_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_PERFMON_RESULT_AVAILABLE_AMD", mrb_fixnum_value(GL_PERFMON_RESULT_AVAILABLE_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_PERFMON_RESULT_SIZE_AMD", mrb_fixnum_value(GL_PERFMON_RESULT_SIZE_AMD));
  mrb_define_const(mrb, mod_gl2ext, "GL_PERFMON_RESULT_AMD", mrb_fixnum_value(GL_PERFMON_RESULT_AMD));
#endif

#ifdef GL_AMD_program_binary_Z400
  mrb_define_const(mrb, mod_gl2ext, "GL_Z400_BINARY_AMD", mrb_fixnum_value(GL_Z400_BINARY_AMD));
#endif

#ifdef GL_EXT_blend_minmax
  mrb_define_const(mrb, mod_gl2ext, "GL_MIN_EXT", mrb_fixnum_value(GL_MIN_EXT));
  mrb_define_const(mrb, mod_gl2ext, "GL_MAX_EXT", mrb_fixnum_value(GL_MAX_EXT));
#endif

#ifdef GL_EXT_discard_framebuffer
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_EXT", mrb_fixnum_value(GL_COLOR_EXT));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_EXT", mrb_fixnum_value(GL_DEPTH_EXT));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_EXT", mrb_fixnum_value(GL_STENCIL_EXT));
#endif

#ifdef GL_EXT_read_format_bgra
  mrb_define_const(mrb, mod_gl2ext, "GL_BGRA_EXT", mrb_fixnum_value(GL_BGRA_EXT));
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT", mrb_fixnum_value(GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT));
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT", mrb_fixnum_value(GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT));
#endif

#ifdef GL_EXT_texture_filter_anisotropic
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_MAX_ANISOTROPY_EXT", mrb_fixnum_value(GL_TEXTURE_MAX_ANISOTROPY_EXT));
  mrb_define_const(mrb, mod_gl2ext, "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT", mrb_fixnum_value(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT));
#endif

#ifdef GL_EXT_texture_format_BGRA8888
  mrb_define_const(mrb, mod_gl2ext, "GL_BGRA_EXT", mrb_fixnum_value(GL_BGRA_EXT));
#endif

#ifdef GL_EXT_texture_type_2_10_10_10_REV
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_INT_2_10_10_10_REV_EXT", mrb_fixnum_value(GL_UNSIGNED_INT_2_10_10_10_REV_EXT));
#endif

#ifdef GL_EXT_texture_compression_dxt1
  mrb_define_const(mrb, mod_gl2ext, "GL_COMPRESSED_RGB_S3TC_DXT1_EXT", mrb_fixnum_value(GL_COMPRESSED_RGB_S3TC_DXT1_EXT));
  mrb_define_const(mrb, mod_gl2ext, "GL_COMPRESSED_RGBA_S3TC_DXT1_EXT", mrb_fixnum_value(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT));
#endif

#ifdef GL_IMG_program_binary
  mrb_define_const(mrb, mod_gl2ext, "GL_SGX_PROGRAM_BINARY_IMG", mrb_fixnum_value(GL_SGX_PROGRAM_BINARY_IMG));
#endif

#ifdef GL_IMG_read_format
  mrb_define_const(mrb, mod_gl2ext, "GL_BGRA_IMG", mrb_fixnum_value(GL_BGRA_IMG));
  mrb_define_const(mrb, mod_gl2ext, "GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG", mrb_fixnum_value(GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG));
#endif

#ifdef GL_IMG_shader_binary
  mrb_define_const(mrb, mod_gl2ext, "GL_SGX_BINARY_IMG", mrb_fixnum_value(GL_SGX_BINARY_IMG));
#endif

#ifdef GL_IMG_texture_compression_pvrtc
  mrb_define_const(mrb, mod_gl2ext, "GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG", mrb_fixnum_value(GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG));
  mrb_define_const(mrb, mod_gl2ext, "GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG", mrb_fixnum_value(GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG));
  mrb_define_const(mrb, mod_gl2ext, "GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG", mrb_fixnum_value(GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG));
  mrb_define_const(mrb, mod_gl2ext, "GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG", mrb_fixnum_value(GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG));
#endif

#ifdef GL_IMG_multisampled_render_to_texture
  mrb_define_const(mrb, mod_gl2ext, "GL_RENDERBUFFER_SAMPLES_IMG", mrb_fixnum_value(GL_RENDERBUFFER_SAMPLES_IMG));
  mrb_define_const(mrb, mod_gl2ext, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG", mrb_fixnum_value(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG));
  mrb_define_const(mrb, mod_gl2ext, "GL_MAX_SAMPLES_IMG", mrb_fixnum_value(GL_MAX_SAMPLES_IMG));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_SAMPLES_IMG", mrb_fixnum_value(GL_TEXTURE_SAMPLES_IMG));
#endif

#ifdef GL_NV_fence
  mrb_define_const(mrb, mod_gl2ext, "GL_ALL_COMPLETED_NV", mrb_fixnum_value(GL_ALL_COMPLETED_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_FENCE_STATUS_NV", mrb_fixnum_value(GL_FENCE_STATUS_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_FENCE_CONDITION_NV", mrb_fixnum_value(GL_FENCE_CONDITION_NV));
#endif

#ifdef GL_NV_coverage_sample
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_COMPONENT_NV", mrb_fixnum_value(GL_COVERAGE_COMPONENT_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_COMPONENT4_NV", mrb_fixnum_value(GL_COVERAGE_COMPONENT4_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_ATTACHMENT_NV", mrb_fixnum_value(GL_COVERAGE_ATTACHMENT_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_BUFFERS_NV", mrb_fixnum_value(GL_COVERAGE_BUFFERS_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_SAMPLES_NV", mrb_fixnum_value(GL_COVERAGE_SAMPLES_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_ALL_FRAGMENTS_NV", mrb_fixnum_value(GL_COVERAGE_ALL_FRAGMENTS_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_EDGE_FRAGMENTS_NV", mrb_fixnum_value(GL_COVERAGE_EDGE_FRAGMENTS_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_AUTOMATIC_NV", mrb_fixnum_value(GL_COVERAGE_AUTOMATIC_NV));
  mrb_define_const(mrb, mod_gl2ext, "GL_COVERAGE_BUFFER_BIT_NV", mrb_fixnum_value(GL_COVERAGE_BUFFER_BIT_NV));
#endif

#ifdef GL_NV_depth_nonlinear
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_COMPONENT16_NONLINEAR_NV", mrb_fixnum_value(GL_DEPTH_COMPONENT16_NONLINEAR_NV));
#endif

#ifdef GL_QCOM_extended_get
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_WIDTH_QCOM", mrb_fixnum_value(GL_TEXTURE_WIDTH_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_HEIGHT_QCOM", mrb_fixnum_value(GL_TEXTURE_HEIGHT_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_DEPTH_QCOM", mrb_fixnum_value(GL_TEXTURE_DEPTH_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_INTERNAL_FORMAT_QCOM", mrb_fixnum_value(GL_TEXTURE_INTERNAL_FORMAT_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_FORMAT_QCOM", mrb_fixnum_value(GL_TEXTURE_FORMAT_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_TYPE_QCOM", mrb_fixnum_value(GL_TEXTURE_TYPE_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_IMAGE_VALID_QCOM", mrb_fixnum_value(GL_TEXTURE_IMAGE_VALID_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_NUM_LEVELS_QCOM", mrb_fixnum_value(GL_TEXTURE_NUM_LEVELS_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_TARGET_QCOM", mrb_fixnum_value(GL_TEXTURE_TARGET_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_TEXTURE_OBJECT_VALID_QCOM", mrb_fixnum_value(GL_TEXTURE_OBJECT_VALID_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STATE_RESTORE", mrb_fixnum_value(GL_STATE_RESTORE));
#endif

#ifdef GL_QCOM_perfmon_global_mode
  mrb_define_const(mrb, mod_gl2ext, "GL_PERFMON_GLOBAL_MODE_QCOM", mrb_fixnum_value(GL_PERFMON_GLOBAL_MODE_QCOM));
#endif

#ifdef GL_QCOM_writeonly_rendering
  mrb_define_const(mrb, mod_gl2ext, "GL_WRITEONLY_RENDERING_QCOM", mrb_fixnum_value(GL_WRITEONLY_RENDERING_QCOM));
#endif

#ifdef GL_QCOM_tiled_rendering
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT0_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT0_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT1_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT1_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT2_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT2_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT3_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT3_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT4_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT4_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT5_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT5_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT6_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT6_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_COLOR_BUFFER_BIT7_QCOM", mrb_fixnum_value(GL_COLOR_BUFFER_BIT7_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT0_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT0_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT1_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT1_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT2_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT2_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT3_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT3_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT4_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT4_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT5_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT5_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT6_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT6_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_DEPTH_BUFFER_BIT7_QCOM", mrb_fixnum_value(GL_DEPTH_BUFFER_BIT7_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT0_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT0_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT1_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT1_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT2_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT2_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT3_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT3_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT4_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT4_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT5_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT5_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT6_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT6_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_STENCIL_BUFFER_BIT7_QCOM", mrb_fixnum_value(GL_STENCIL_BUFFER_BIT7_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT0_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT0_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT1_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT1_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT2_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT2_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT3_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT3_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT4_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT4_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT5_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT5_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT6_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT6_QCOM));
  mrb_define_const(mrb, mod_gl2ext, "GL_MULTISAMPLE_BUFFER_BIT7_QCOM", mrb_fixnum_value(GL_MULTISAMPLE_BUFFER_BIT7_QCOM));
#endif
}
