#mruby-gles

OpenGL ES 2.0 bindings for mruby.

#Link flags

A flag is usually needed to link the corresponding OpenGL ES library on your system. Each system may have different flags for this. Please consult to the documentation of your OS/system of choice for details.

When you have the flag, you have several options on how to add the flag:

* If the flag is of format `-lgl`(for example on Linux systems), you can set the environment variable `GLES_LINK_LIBRARY` to `gl`. `mruby-gles` gem will pick up the flag for you
* However, if you have a flag like `-framework OpenGL`(on Mac OS X), you need to use another environment variable `GLES_LINK_FLAG`. Set it to `-framework OpenGL` and you are good to go.
* Besides the 2 options above, you can always add the flag in your mruby build config file, or add that to your build system in order to make this work.

#Why don't we use ffi?

For the time being, I failed to find a proper implementation that works both when compiling mruby natively, and when using in [webruby](https://github.com/xxuejie/webruby). What's more, one design philosophy of mruby is not to include anything you do not need. Considering OpenGL ES does not require the full functionalities of ffi, it may be overkilled to introduce a ffi implementation here.

As a result, this gem is currently implemented by hand without using any ffi. That being said, I'm still open to changing to a ffi implementation if we discover a better-yet-still-light-weighted solution for both native case and JS case(webruby).

#License

This project is distributed under the MIT License. See LICENSE for further details.
