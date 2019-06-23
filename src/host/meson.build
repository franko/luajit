build_cpu_family = build_machine.cpu_family()

minilua = executable('minilua', 'minilua.c', dependencies: libm, install: false)

lj_arch_run = cc.run(lj_arch_test_file)
if not lj_arch_run.compiled() or lj_arch_run.returncode() != 0
    error('error running luajit arch testing program: ' + lj_arch_run.stderr())
endif
lj_arch_list = lj_arch_run.stdout().split(':')
lj_arch = lj_arch_list[0]
dasm_arch = lj_arch_list[1]
buildvm_defines_output = lj_arch_list[2]
dasm_args_output = lj_arch_list[3]

dasm_args = [minilua, dynasm]
dasm_args += dasm_args_output.split(',')
dasm_args += ['-o', '@OUTPUT@', '@INPUT@']

buildvm_defines = buildvm_defines_output.split(',')
dasm_dasc = files('../vm_' + dasm_arch + '.dasc')

message('arch: ' + lj_arch)
message('dasm arch: ' + dasm_arch)
message('buildvm defines: ' + buildvm_defines_output)
message('dasm args: ' + dasm_args_output)

buildvm_arch_h = custom_target('buildvm_arch.h',
    input : dasm_dasc,
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
