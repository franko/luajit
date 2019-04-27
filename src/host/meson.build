build_cpu_family = build_machine.cpu_family()

lj_arch = {'x86_64': 'x64', 'x86': 'x86', 'arm': 'arm', 'ppc': 'ppc', 'mips': 'mips'}

# TODO: ppcspe, mipsel

if build_cpu_family in lj_arch
    target_arch = lj_arch[build_cpu_family]
else
    error('Unsupported target architecture: ' + build_cpu_family)
endif

buildvm_defines = ['-DLUAJIT_TARGET=LUAJIT_ARCH_' + target_arch]
buildvm_defines += '-DLJ_ARCH_HASFPU=1'
buildvm_defines += '-DLJ_ABI_SOFTFP=0'

minilua = executable('minilua', 'minilua.c', dependencies: libm, install: false)

buildvm_arch_h = custom_target('buildvm_arch.h',
    input : vm_x86_dasc,
    output : 'buildvm_arch.h',
    command : [minilua, dynasm, '-D', 'P64', '-D', 'JIT', '-D', 'FFI', '-D', 'FPU', '-D', 'HFABI', '-D', 'VER=', '-o', '@OUTPUT@', '@INPUT@']
)

buildvm_sources = ['buildvm.c', 'buildvm_asm.c', 'buildvm_peobj.c', 'buildvm_lib.c', 'buildvm_fold.c']
buildvm_sources += buildvm_arch_h

buildvm = executable('buildvm',
    buildvm_sources,
    include_directories: luajit_source_dir,
    c_args: buildvm_defines,
    dependencies: libm,
    install: false
)
