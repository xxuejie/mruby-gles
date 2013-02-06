#include <stdlib.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/string.h>

#include <GL/glut.h>

/* TODO: this is not finished yet! Most functions are not added here. */

static mrb_value
mrb_glut_init(mrb_state* mrb, mrb_value mod)
{
  mrb_value args, ret;
  int argc, i;
  char** argv;

  mrb_get_args(mrb, "A", &args);
  argc = RARRAY_LEN(args);
  argv = (char**) malloc(argc * sizeof(char*));

  for (i = 0; i < argc; i++) {
    argv[i] = mrb_string_value_ptr(mrb, RARRAY_PTR(args)[i]);
  }

  glutInit(&argc, argv);

  ret = mrb_ary_new(mrb);
  for (i = 0; i < argc; i++) {
    mrb_ary_push(mrb, ret, mrb_str_new2(mrb, argv[i]));
  }

  free(argv);
  return ret;
}

void
mrb_mruby_gles_gem_glut_init(mrb_state* mrb)
{
  struct RClass *mod_glut = mrb_define_module(mrb, "GLUT");

  mrb_define_const(mrb, mod_glut, "FREEGLUT", mrb_fixnum_value(FREEGLUT));
  mrb_define_const(mrb, mod_glut, "GLUT_API_VERSION", mrb_fixnum_value(GLUT_API_VERSION));
  mrb_define_const(mrb, mod_glut, "FREEGLUT_VERSION_2_0", mrb_fixnum_value(FREEGLUT_VERSION_2_0));
  mrb_define_const(mrb, mod_glut, "GLUT_XLIB_IMPLEMENTATION", mrb_fixnum_value(GLUT_XLIB_IMPLEMENTATION));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F1", mrb_fixnum_value(GLUT_KEY_F1));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F2", mrb_fixnum_value(GLUT_KEY_F2));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F3", mrb_fixnum_value(GLUT_KEY_F3));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F4", mrb_fixnum_value(GLUT_KEY_F4));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F5", mrb_fixnum_value(GLUT_KEY_F5));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F6", mrb_fixnum_value(GLUT_KEY_F6));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F7", mrb_fixnum_value(GLUT_KEY_F7));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F8", mrb_fixnum_value(GLUT_KEY_F8));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F9", mrb_fixnum_value(GLUT_KEY_F9));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F10", mrb_fixnum_value(GLUT_KEY_F10));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F11", mrb_fixnum_value(GLUT_KEY_F11));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_F12", mrb_fixnum_value(GLUT_KEY_F12));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_LEFT", mrb_fixnum_value(GLUT_KEY_LEFT));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_UP", mrb_fixnum_value(GLUT_KEY_UP));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_RIGHT", mrb_fixnum_value(GLUT_KEY_RIGHT));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_DOWN", mrb_fixnum_value(GLUT_KEY_DOWN));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_PAGE_UP", mrb_fixnum_value(GLUT_KEY_PAGE_UP));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_PAGE_DOWN", mrb_fixnum_value(GLUT_KEY_PAGE_DOWN));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_HOME", mrb_fixnum_value(GLUT_KEY_HOME));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_END", mrb_fixnum_value(GLUT_KEY_END));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_INSERT", mrb_fixnum_value(GLUT_KEY_INSERT));
  mrb_define_const(mrb, mod_glut, "GLUT_LEFT_BUTTON", mrb_fixnum_value(GLUT_LEFT_BUTTON));
  mrb_define_const(mrb, mod_glut, "GLUT_MIDDLE_BUTTON", mrb_fixnum_value(GLUT_MIDDLE_BUTTON));
  mrb_define_const(mrb, mod_glut, "GLUT_RIGHT_BUTTON", mrb_fixnum_value(GLUT_RIGHT_BUTTON));
  mrb_define_const(mrb, mod_glut, "GLUT_DOWN", mrb_fixnum_value(GLUT_DOWN));
  mrb_define_const(mrb, mod_glut, "GLUT_UP", mrb_fixnum_value(GLUT_UP));
  mrb_define_const(mrb, mod_glut, "GLUT_LEFT", mrb_fixnum_value(GLUT_LEFT));
  mrb_define_const(mrb, mod_glut, "GLUT_ENTERED", mrb_fixnum_value(GLUT_ENTERED));
  mrb_define_const(mrb, mod_glut, "GLUT_RGB", mrb_fixnum_value(GLUT_RGB));
  mrb_define_const(mrb, mod_glut, "GLUT_RGBA", mrb_fixnum_value(GLUT_RGBA));
  mrb_define_const(mrb, mod_glut, "GLUT_INDEX", mrb_fixnum_value(GLUT_INDEX));
  mrb_define_const(mrb, mod_glut, "GLUT_SINGLE", mrb_fixnum_value(GLUT_SINGLE));
  mrb_define_const(mrb, mod_glut, "GLUT_DOUBLE", mrb_fixnum_value(GLUT_DOUBLE));
  mrb_define_const(mrb, mod_glut, "GLUT_ACCUM", mrb_fixnum_value(GLUT_ACCUM));
  mrb_define_const(mrb, mod_glut, "GLUT_ALPHA", mrb_fixnum_value(GLUT_ALPHA));
  mrb_define_const(mrb, mod_glut, "GLUT_DEPTH", mrb_fixnum_value(GLUT_DEPTH));
  mrb_define_const(mrb, mod_glut, "GLUT_STENCIL", mrb_fixnum_value(GLUT_STENCIL));
  mrb_define_const(mrb, mod_glut, "GLUT_MULTISAMPLE", mrb_fixnum_value(GLUT_MULTISAMPLE));
  mrb_define_const(mrb, mod_glut, "GLUT_STEREO", mrb_fixnum_value(GLUT_STEREO));
  mrb_define_const(mrb, mod_glut, "GLUT_LUMINANCE", mrb_fixnum_value(GLUT_LUMINANCE));
  mrb_define_const(mrb, mod_glut, "GLUT_MENU_NOT_IN_USE", mrb_fixnum_value(GLUT_MENU_NOT_IN_USE));
  mrb_define_const(mrb, mod_glut, "GLUT_MENU_IN_USE", mrb_fixnum_value(GLUT_MENU_IN_USE));
  mrb_define_const(mrb, mod_glut, "GLUT_NOT_VISIBLE", mrb_fixnum_value(GLUT_NOT_VISIBLE));
  mrb_define_const(mrb, mod_glut, "GLUT_VISIBLE", mrb_fixnum_value(GLUT_VISIBLE));
  mrb_define_const(mrb, mod_glut, "GLUT_HIDDEN", mrb_fixnum_value(GLUT_HIDDEN));
  mrb_define_const(mrb, mod_glut, "GLUT_FULLY_RETAINED", mrb_fixnum_value(GLUT_FULLY_RETAINED));
  mrb_define_const(mrb, mod_glut, "GLUT_PARTIALLY_RETAINED", mrb_fixnum_value(GLUT_PARTIALLY_RETAINED));
  mrb_define_const(mrb, mod_glut, "GLUT_FULLY_COVERED", mrb_fixnum_value(GLUT_FULLY_COVERED));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_X", mrb_fixnum_value(GLUT_WINDOW_X));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_Y", mrb_fixnum_value(GLUT_WINDOW_Y));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_WIDTH", mrb_fixnum_value(GLUT_WINDOW_WIDTH));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_HEIGHT", mrb_fixnum_value(GLUT_WINDOW_HEIGHT));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_BUFFER_SIZE", mrb_fixnum_value(GLUT_WINDOW_BUFFER_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_STENCIL_SIZE", mrb_fixnum_value(GLUT_WINDOW_STENCIL_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_DEPTH_SIZE", mrb_fixnum_value(GLUT_WINDOW_DEPTH_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_RED_SIZE", mrb_fixnum_value(GLUT_WINDOW_RED_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_GREEN_SIZE", mrb_fixnum_value(GLUT_WINDOW_GREEN_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_BLUE_SIZE", mrb_fixnum_value(GLUT_WINDOW_BLUE_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_ALPHA_SIZE", mrb_fixnum_value(GLUT_WINDOW_ALPHA_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_ACCUM_RED_SIZE", mrb_fixnum_value(GLUT_WINDOW_ACCUM_RED_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_ACCUM_GREEN_SIZE", mrb_fixnum_value(GLUT_WINDOW_ACCUM_GREEN_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_ACCUM_BLUE_SIZE", mrb_fixnum_value(GLUT_WINDOW_ACCUM_BLUE_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_ACCUM_ALPHA_SIZE", mrb_fixnum_value(GLUT_WINDOW_ACCUM_ALPHA_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_DOUBLEBUFFER", mrb_fixnum_value(GLUT_WINDOW_DOUBLEBUFFER));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_RGBA", mrb_fixnum_value(GLUT_WINDOW_RGBA));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_PARENT", mrb_fixnum_value(GLUT_WINDOW_PARENT));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_NUM_CHILDREN", mrb_fixnum_value(GLUT_WINDOW_NUM_CHILDREN));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_COLORMAP_SIZE", mrb_fixnum_value(GLUT_WINDOW_COLORMAP_SIZE));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_NUM_SAMPLES", mrb_fixnum_value(GLUT_WINDOW_NUM_SAMPLES));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_STEREO", mrb_fixnum_value(GLUT_WINDOW_STEREO));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_CURSOR", mrb_fixnum_value(GLUT_WINDOW_CURSOR));
  mrb_define_const(mrb, mod_glut, "GLUT_SCREEN_WIDTH", mrb_fixnum_value(GLUT_SCREEN_WIDTH));
  mrb_define_const(mrb, mod_glut, "GLUT_SCREEN_HEIGHT", mrb_fixnum_value(GLUT_SCREEN_HEIGHT));
  mrb_define_const(mrb, mod_glut, "GLUT_SCREEN_WIDTH_MM", mrb_fixnum_value(GLUT_SCREEN_WIDTH_MM));
  mrb_define_const(mrb, mod_glut, "GLUT_SCREEN_HEIGHT_MM", mrb_fixnum_value(GLUT_SCREEN_HEIGHT_MM));
  mrb_define_const(mrb, mod_glut, "GLUT_MENU_NUM_ITEMS", mrb_fixnum_value(GLUT_MENU_NUM_ITEMS));
  mrb_define_const(mrb, mod_glut, "GLUT_DISPLAY_MODE_POSSIBLE", mrb_fixnum_value(GLUT_DISPLAY_MODE_POSSIBLE));
  mrb_define_const(mrb, mod_glut, "GLUT_INIT_WINDOW_X", mrb_fixnum_value(GLUT_INIT_WINDOW_X));
  mrb_define_const(mrb, mod_glut, "GLUT_INIT_WINDOW_Y", mrb_fixnum_value(GLUT_INIT_WINDOW_Y));
  mrb_define_const(mrb, mod_glut, "GLUT_INIT_WINDOW_WIDTH", mrb_fixnum_value(GLUT_INIT_WINDOW_WIDTH));
  mrb_define_const(mrb, mod_glut, "GLUT_INIT_WINDOW_HEIGHT", mrb_fixnum_value(GLUT_INIT_WINDOW_HEIGHT));
  mrb_define_const(mrb, mod_glut, "GLUT_INIT_DISPLAY_MODE", mrb_fixnum_value(GLUT_INIT_DISPLAY_MODE));
  mrb_define_const(mrb, mod_glut, "GLUT_ELAPSED_TIME", mrb_fixnum_value(GLUT_ELAPSED_TIME));
  mrb_define_const(mrb, mod_glut, "GLUT_WINDOW_FORMAT_ID", mrb_fixnum_value(GLUT_WINDOW_FORMAT_ID));
  mrb_define_const(mrb, mod_glut, "GLUT_HAS_KEYBOARD", mrb_fixnum_value(GLUT_HAS_KEYBOARD));
  mrb_define_const(mrb, mod_glut, "GLUT_HAS_MOUSE", mrb_fixnum_value(GLUT_HAS_MOUSE));
  mrb_define_const(mrb, mod_glut, "GLUT_HAS_SPACEBALL", mrb_fixnum_value(GLUT_HAS_SPACEBALL));
  mrb_define_const(mrb, mod_glut, "GLUT_HAS_DIAL_AND_BUTTON_BOX", mrb_fixnum_value(GLUT_HAS_DIAL_AND_BUTTON_BOX));
  mrb_define_const(mrb, mod_glut, "GLUT_HAS_TABLET", mrb_fixnum_value(GLUT_HAS_TABLET));
  mrb_define_const(mrb, mod_glut, "GLUT_NUM_MOUSE_BUTTONS", mrb_fixnum_value(GLUT_NUM_MOUSE_BUTTONS));
  mrb_define_const(mrb, mod_glut, "GLUT_NUM_SPACEBALL_BUTTONS", mrb_fixnum_value(GLUT_NUM_SPACEBALL_BUTTONS));
  mrb_define_const(mrb, mod_glut, "GLUT_NUM_BUTTON_BOX_BUTTONS", mrb_fixnum_value(GLUT_NUM_BUTTON_BOX_BUTTONS));
  mrb_define_const(mrb, mod_glut, "GLUT_NUM_DIALS", mrb_fixnum_value(GLUT_NUM_DIALS));
  mrb_define_const(mrb, mod_glut, "GLUT_NUM_TABLET_BUTTONS", mrb_fixnum_value(GLUT_NUM_TABLET_BUTTONS));
  mrb_define_const(mrb, mod_glut, "GLUT_DEVICE_IGNORE_KEY_REPEAT", mrb_fixnum_value(GLUT_DEVICE_IGNORE_KEY_REPEAT));
  mrb_define_const(mrb, mod_glut, "GLUT_DEVICE_KEY_REPEAT", mrb_fixnum_value(GLUT_DEVICE_KEY_REPEAT));
  mrb_define_const(mrb, mod_glut, "GLUT_HAS_JOYSTICK", mrb_fixnum_value(GLUT_HAS_JOYSTICK));
  mrb_define_const(mrb, mod_glut, "GLUT_OWNS_JOYSTICK", mrb_fixnum_value(GLUT_OWNS_JOYSTICK));
  mrb_define_const(mrb, mod_glut, "GLUT_JOYSTICK_BUTTONS", mrb_fixnum_value(GLUT_JOYSTICK_BUTTONS));
  mrb_define_const(mrb, mod_glut, "GLUT_JOYSTICK_AXES", mrb_fixnum_value(GLUT_JOYSTICK_AXES));
  mrb_define_const(mrb, mod_glut, "GLUT_JOYSTICK_POLL_RATE", mrb_fixnum_value(GLUT_JOYSTICK_POLL_RATE));
  mrb_define_const(mrb, mod_glut, "GLUT_OVERLAY_POSSIBLE", mrb_fixnum_value(GLUT_OVERLAY_POSSIBLE));
  mrb_define_const(mrb, mod_glut, "GLUT_LAYER_IN_USE", mrb_fixnum_value(GLUT_LAYER_IN_USE));
  mrb_define_const(mrb, mod_glut, "GLUT_HAS_OVERLAY", mrb_fixnum_value(GLUT_HAS_OVERLAY));
  mrb_define_const(mrb, mod_glut, "GLUT_TRANSPARENT_INDEX", mrb_fixnum_value(GLUT_TRANSPARENT_INDEX));
  mrb_define_const(mrb, mod_glut, "GLUT_NORMAL_DAMAGED", mrb_fixnum_value(GLUT_NORMAL_DAMAGED));
  mrb_define_const(mrb, mod_glut, "GLUT_OVERLAY_DAMAGED", mrb_fixnum_value(GLUT_OVERLAY_DAMAGED));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_POSSIBLE", mrb_fixnum_value(GLUT_VIDEO_RESIZE_POSSIBLE));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_IN_USE", mrb_fixnum_value(GLUT_VIDEO_RESIZE_IN_USE));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_X_DELTA", mrb_fixnum_value(GLUT_VIDEO_RESIZE_X_DELTA));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_Y_DELTA", mrb_fixnum_value(GLUT_VIDEO_RESIZE_Y_DELTA));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_WIDTH_DELTA", mrb_fixnum_value(GLUT_VIDEO_RESIZE_WIDTH_DELTA));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_HEIGHT_DELTA", mrb_fixnum_value(GLUT_VIDEO_RESIZE_HEIGHT_DELTA));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_X", mrb_fixnum_value(GLUT_VIDEO_RESIZE_X));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_Y", mrb_fixnum_value(GLUT_VIDEO_RESIZE_Y));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_WIDTH", mrb_fixnum_value(GLUT_VIDEO_RESIZE_WIDTH));
  mrb_define_const(mrb, mod_glut, "GLUT_VIDEO_RESIZE_HEIGHT", mrb_fixnum_value(GLUT_VIDEO_RESIZE_HEIGHT));
  mrb_define_const(mrb, mod_glut, "GLUT_NORMAL", mrb_fixnum_value(GLUT_NORMAL));
  mrb_define_const(mrb, mod_glut, "GLUT_OVERLAY", mrb_fixnum_value(GLUT_OVERLAY));
  mrb_define_const(mrb, mod_glut, "GLUT_ACTIVE_SHIFT", mrb_fixnum_value(GLUT_ACTIVE_SHIFT));
  mrb_define_const(mrb, mod_glut, "GLUT_ACTIVE_CTRL", mrb_fixnum_value(GLUT_ACTIVE_CTRL));
  mrb_define_const(mrb, mod_glut, "GLUT_ACTIVE_ALT", mrb_fixnum_value(GLUT_ACTIVE_ALT));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_RIGHT_ARROW", mrb_fixnum_value(GLUT_CURSOR_RIGHT_ARROW));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_LEFT_ARROW", mrb_fixnum_value(GLUT_CURSOR_LEFT_ARROW));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_INFO", mrb_fixnum_value(GLUT_CURSOR_INFO));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_DESTROY", mrb_fixnum_value(GLUT_CURSOR_DESTROY));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_HELP", mrb_fixnum_value(GLUT_CURSOR_HELP));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_CYCLE", mrb_fixnum_value(GLUT_CURSOR_CYCLE));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_SPRAY", mrb_fixnum_value(GLUT_CURSOR_SPRAY));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_WAIT", mrb_fixnum_value(GLUT_CURSOR_WAIT));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_TEXT", mrb_fixnum_value(GLUT_CURSOR_TEXT));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_CROSSHAIR", mrb_fixnum_value(GLUT_CURSOR_CROSSHAIR));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_UP_DOWN", mrb_fixnum_value(GLUT_CURSOR_UP_DOWN));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_LEFT_RIGHT", mrb_fixnum_value(GLUT_CURSOR_LEFT_RIGHT));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_TOP_SIDE", mrb_fixnum_value(GLUT_CURSOR_TOP_SIDE));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_BOTTOM_SIDE", mrb_fixnum_value(GLUT_CURSOR_BOTTOM_SIDE));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_LEFT_SIDE", mrb_fixnum_value(GLUT_CURSOR_LEFT_SIDE));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_RIGHT_SIDE", mrb_fixnum_value(GLUT_CURSOR_RIGHT_SIDE));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_TOP_LEFT_CORNER", mrb_fixnum_value(GLUT_CURSOR_TOP_LEFT_CORNER));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_TOP_RIGHT_CORNER", mrb_fixnum_value(GLUT_CURSOR_TOP_RIGHT_CORNER));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_BOTTOM_RIGHT_CORNER", mrb_fixnum_value(GLUT_CURSOR_BOTTOM_RIGHT_CORNER));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_BOTTOM_LEFT_CORNER", mrb_fixnum_value(GLUT_CURSOR_BOTTOM_LEFT_CORNER));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_INHERIT", mrb_fixnum_value(GLUT_CURSOR_INHERIT));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_NONE", mrb_fixnum_value(GLUT_CURSOR_NONE));
  mrb_define_const(mrb, mod_glut, "GLUT_CURSOR_FULL_CROSSHAIR", mrb_fixnum_value(GLUT_CURSOR_FULL_CROSSHAIR));
  mrb_define_const(mrb, mod_glut, "GLUT_RED", mrb_fixnum_value(GLUT_RED));
  mrb_define_const(mrb, mod_glut, "GLUT_GREEN", mrb_fixnum_value(GLUT_GREEN));
  mrb_define_const(mrb, mod_glut, "GLUT_BLUE", mrb_fixnum_value(GLUT_BLUE));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_REPEAT_OFF", mrb_fixnum_value(GLUT_KEY_REPEAT_OFF));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_REPEAT_ON", mrb_fixnum_value(GLUT_KEY_REPEAT_ON));
  mrb_define_const(mrb, mod_glut, "GLUT_KEY_REPEAT_DEFAULT", mrb_fixnum_value(GLUT_KEY_REPEAT_DEFAULT));
  mrb_define_const(mrb, mod_glut, "GLUT_JOYSTICK_BUTTON_A", mrb_fixnum_value(GLUT_JOYSTICK_BUTTON_A));
  mrb_define_const(mrb, mod_glut, "GLUT_JOYSTICK_BUTTON_B", mrb_fixnum_value(GLUT_JOYSTICK_BUTTON_B));
  mrb_define_const(mrb, mod_glut, "GLUT_JOYSTICK_BUTTON_C", mrb_fixnum_value(GLUT_JOYSTICK_BUTTON_C));
  mrb_define_const(mrb, mod_glut, "GLUT_JOYSTICK_BUTTON_D", mrb_fixnum_value(GLUT_JOYSTICK_BUTTON_D));
  mrb_define_const(mrb, mod_glut, "GLUT_GAME_MODE_ACTIVE", mrb_fixnum_value(GLUT_GAME_MODE_ACTIVE));
  mrb_define_const(mrb, mod_glut, "GLUT_GAME_MODE_POSSIBLE", mrb_fixnum_value(GLUT_GAME_MODE_POSSIBLE));
  mrb_define_const(mrb, mod_glut, "GLUT_GAME_MODE_WIDTH", mrb_fixnum_value(GLUT_GAME_MODE_WIDTH));
  mrb_define_const(mrb, mod_glut, "GLUT_GAME_MODE_HEIGHT", mrb_fixnum_value(GLUT_GAME_MODE_HEIGHT));
  mrb_define_const(mrb, mod_glut, "GLUT_GAME_MODE_PIXEL_DEPTH", mrb_fixnum_value(GLUT_GAME_MODE_PIXEL_DEPTH));
  mrb_define_const(mrb, mod_glut, "GLUT_GAME_MODE_REFRESH_RATE", mrb_fixnum_value(GLUT_GAME_MODE_REFRESH_RATE));
  mrb_define_const(mrb, mod_glut, "GLUT_GAME_MODE_DISPLAY_CHANGED", mrb_fixnum_value(GLUT_GAME_MODE_DISPLAY_CHANGED));

  mrb_define_module_function(mrb, mod_glut, "glutInit", mrb_glut_init, ARGS_REQ(1));
}
