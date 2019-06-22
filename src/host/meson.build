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

lj_arch_run = cc.run(lj_arch_test_file)
if not lj_arch_run.compiled() or lj_arch_run.returncode() != 0
    error('error running luajit arch testing program: ' + lj_arch_run.stderr())
endif
lj_arch_list = lj_arch_run.stdout().split(':')
lj_arch_DEBUG = lj_arch_list[0]
dasm_arch = lj_arch_list[1]
target_arch_flags = lj_arch_list[2] # .split(',')
dasm_args_output = lj_arch_list[3]

dasm_args = [minilua, dynasm]
dasm_args += dasm_args_output.split(',')
dasm_args += ['-o', '@OUTPUT@', '@INPUT@']

message('arch: ' + lj_arch_DEBUG)
message('dasm arch: ' + dasm_arch)
message('flags' + target_arch_flags)
message('dasm args' + dasm_args_output)

buildvm_arch_h = custom_target('buildvm_arch.h',
    input : vm_x86_dasc,
    output : 'buildvm_arch.h',
    command : dasm_args,
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
