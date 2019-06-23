#include <stdio.h>
#include <stdlib.h>
#include "lj_arch.h"

/* Print in stdout the following string:

   <TARGET_LJARCH>:<DASM ARCH>:<TARGET_ARCH>:<DASM_AFLAGS>

   Where <TARGET_ARCH> are <DASM_AFLAGS> comma separated strings.

   Each value correspond to the variable of the same name in Luajit's
   original Makefile.
*/

#define MAIN_SEPARATOR ":"
#define DEFS_SEPARATOR ","

struct string_array {
    const char **data;
    int length;
    int size;
};

static int upper_pow2(int v) {
    if (v > 0) {
        // compute the next highest power of 2 of 32-bit v
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
    }
    return v;
}

static void string_array_ensure_size(struct string_array *array, const int new_length) {
    if (new_length <= array->size) return;
    const int new_size = upper_pow2(new_length);
    const char **new_data = realloc(array->data, new_size * sizeof(const char *));
    if (new_data == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    array->data = new_data;
    array->size = new_size;
}

static void string_array_init(struct string_array *array) {
    const int init_size = 32;
    array->length = 0;
    array->size = 0;
    array->data = NULL;
    string_array_ensure_size(array, init_size);
}

static void string_array_append(struct string_array *array, const char *s) {
    string_array_ensure_size(array, array->length + 1);
    array->data[array->length++] = s;
}

static void add_def(struct string_array *args, const char *def) {
    string_array_append(args, "-D");
    string_array_append(args, def);
}

int main() {
const char *lj_arch, *dasm_arch;
struct string_array arch_defs[1];
string_array_init(arch_defs);

#ifdef LJ_TARGET_X64
lj_arch = "x64";
#elif LJ_TARGET_X86
lj_arch = "x86";
#elif LJ_TARGET_ARM
lj_arch = "arm";
#elif LJ_TARGET_PPC
lj_arch = "ppc";
#elif LJ_TARGET_PPCSPE
lj_arch = "ppcspe";
#elif LJ_TARGET_MIPS
lj_arch = "mips";
#ifdef MIPSEL
string_array_append(arch_defs, "-D__MIPSEL__=1");
#endif
#else
fprintf(stderr, "Unsupported architecture\n");
exit(1);
#endif

char luajit_target_def[128];
sprintf(luajit_target_def, "-DLUAJIT_TARGET=LUAJIT_ARCH_%s", lj_arch);
string_array_append(arch_defs, luajit_target_def);

#ifdef LJ_TARGET_X64
dasm_arch = "x86";
#else
dasm_arch = lj_arch;
#endif

struct string_array dasm[1];
string_array_init(dasm);

#if LJ_ARCH_BITS == 64
add_def(dasm, "P64");
#endif
#if LJ_HASJIT == 1
add_def(dasm, "JIT");
#endif
#if LJ_HASFFI == 1
add_def(dasm, "FFI");
#endif
#if LJ_DUALNUM == 1
add_def(dasm, "DUALNUM");
#endif
#if LJ_ARCH_HASFPU == 1
add_def(dasm, "FPU");
string_array_append(arch_defs, "-DLJ_ARCH_HASFPU=1");
#else
string_array_append(arch_defs, "-DLJ_ARCH_HASFPU=0");
#endif
#if LJ_ABI_SOFTFP == 1
string_array_append(arch_defs, "-DLJ_ABI_SOFTFP=1");
#else
add_def(dasm, "HFABI");
string_array_append(arch_defs, "-DLJ_ABI_SOFTFP=0");
#endif
#if LJ_NO_UNWIND == 1
add_def(dasm, "NO_UNWIND");
string_array_append(arch_defs, "-DLUAJIT_NO_UNWIND");
#endif

char arm_arch_version[16];
#if LJ_ARCH_VERSION
sprintf(arm_arch_version, "VER=%d", LJ_ARCH_VERSION);
#else
sprintf(arm_arch_version, "VER=");
#endif
add_def(dasm, arm_arch_version);

#ifdef _WIN32
add_def(dasm, "WIN");
#endif

#if (!defined LJ_TARGET_X64 && defined LJ_TARGET_X86) && __SSE2__ == 1
add_def(dasm, "SSE");
#endif

printf("%s%s%s%s", lj_arch, MAIN_SEPARATOR, dasm_arch, MAIN_SEPARATOR);
for (int i = 0; i < arch_defs->length; i++) {
	printf("%s%s", i > 0 ? DEFS_SEPARATOR : "", arch_defs->data[i]);
}
printf("%s", MAIN_SEPARATOR);
for (int i = 0; i < dasm->length; i++) {
	printf("%s%s", i > 0 ? DEFS_SEPARATOR : "", dasm->data[i]);
}
printf("\n");

return 0;
}
