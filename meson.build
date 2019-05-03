project('luajit', 'c', version : '2.0.5')

cc = meson.get_compiler('c')
libm = cc.find_library('m', required : false)
libdl = cc.find_library('dl', required : false)
luajit_source_dir = include_directories('src')

dynasm = files('dynasm/dynasm.lua')
vm_x86_dasc = files('src/vm_x86.dasc')

subdir('src')
