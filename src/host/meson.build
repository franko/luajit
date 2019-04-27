build_cpu_family = build_machine.cpu_family()

lj_arch = {'x86_64': 'x64', 'x86': 'x86', 'arm': 'arm', 'ppc': 'ppc', 'mips': 'mips'}

# TODO: ppcspe, mipsel

if build_cpu_family in lj_arch
    target_arch = lj_arch[build_cpu_family]
else
    error('Unsupported target architecture: ' + build_cpu_family)
endif

minilua_defines = ['-DLUAJIT_TARGET=LUAJIT_ARCH_' + target_arch]
minilua_defines += '-DLJ_ARCH_HASFPU=1'
minilua_defines += '-DLJ_ABI_SOFTFP=0'

executable('minilua',
    'minilua.c',
    include_directories: luajit_source_dir,
    c_args: minilua_defines,
    dependencies: libm,
    install: false)
