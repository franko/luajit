project('luajit', 'c', version : '2.0.5', default_options : 'c_std=c99')

cc = meson.get_compiler('c')
libm = cc.find_library('m', required : false)
luajit_source_dir = include_directories('src')

subdir('src')
