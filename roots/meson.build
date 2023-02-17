subdir('src')
subdir('include')

src_dir_lib = meson.current_source_dir()

sources_lib = [sources]
include_lib = [include]
headers_lib = [headers]

lib_roots  = library('roots',
                     sources_lib,
                     include_directories : include_lib,
                     implicit_include_directories : true,
                     install : true)

dep_roots = declare_dependency(include_directories : include_lib,
                               link_with : lib_roots)
