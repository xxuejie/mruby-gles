#mruby-gles

OpenGL ES 2.0 bindings for mruby.

#Why don't we use ffi?

For the time being, I failed to find a proper implementation that works both when compiling mruby natively, and when using in [webruby](https://github.com/xxuejie/webruby). What's more, one design philosophy of mruby is not to include anything you do not need. Considering OpenGL ES does not require the full functionalities of ffi, it may be overkilled to introduce a ffi implementation here.

As a result, this gem is currently implemented by hand without using any ffi. That being said, I'm still open to changing to a ffi implementation if we discover a better-yet-still-light-weighted solution for both native case and JS case(webruby).

#License

This project is distributed under the MIT License. See LICENSE for further details.
