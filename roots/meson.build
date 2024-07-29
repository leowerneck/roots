subdir('src')
subdir('include')

src_dir_lib = meson.current_source_dir()

sources_lib = [sources]
include_lib = [include]
headers_lib = [headers]

cc = meson.get_compiler('c')
mdep = cc.find_library('m', required : true)

lib_roots = library(
  'roots',
  sources_lib,
  include_directories : include_lib,
  implicit_include_directories : true,
  install : true,
  dependencies : mdep
)

dep_roots = declare_dependency(include_directories : include_lib,
                               link_with : lib_roots)
