project('luajit', 'c', version : '2.1.0-beta3', default_options : ['c_winlibs='])

pkg = import('pkgconfig')

cc = meson.get_compiler('c')
libm = cc.find_library('m', required : false)
libdl = cc.find_library('dl', required : false)
luajit_dependencies = [libm, libdl]

luajit_source_dir = include_directories('src')
luajit_abiver = '51'

dynasm = files('dynasm/dynasm.lua')

install_man('etc/luajit.1')

subdir('src')
