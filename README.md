#mruby-gles

OpenGL ES 2.0 bindings for mruby.

Special thanks to the [ruby-opengl](http://ruby-opengl.rubyforge.org/) project(a git mirror can be found at [here](https://github.com/theymaybecoders/ruby-opengl)). A lot of ideas used in this gem, including the handling of `GLvoid*` type using `Array#pack` and `String#unpack` and the macro-style function generation framework in `src/mrb_gl_defs.h`, are obtained from reading the ruby-opengl project.

#License

This project is distributed under the MIT License. See LICENSE for further details.
