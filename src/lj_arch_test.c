#include <stdio.h>
#include "lj_arch.h"

/* Find all string used in Makefile with command

   cat Makefile | awk '/findstring .+TARGET_TESTARCH/'
*/

#define QUOTE(X) #X
#define MAIN_SEPARATOR ":"
#define DEFS_SEPARATOR ","

int main() {
const char *lj_arch, *dasm_arch;
const char *arch_defs[128];
int arch_defs_n = 0;

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
arch_defs[arch_defs_n++] = "-D__MIPSEL__=1";
#endif
#else
fprintf(stderr, "Unsupported architecture\n");
exit(1);
#endif

#ifdef LJ_TARGET_X64
dasm_arch = "x86";
#else
dasm_arch = lj_arch;
#endif

const char *dasm[128];
int dasm_n = 0;

#if LJ_ARCH_BITS == 64
dasm[dasm_n++] = "-D P64";
#endif
#if LJ_HASJIT == 1
dasm[dasm_n++] = "-D JIT";
#endif
#if LJ_HASFFI == 1
dasm[dasm_n++] = "-D FFI";
#endif
#if LJ_DUALNUM == 1
dasm[dasm_n++] = "-D DUALNUM";
#endif
#if LJ_ARCH_HASFPU == 1
dasm[dasm_n++] = "-D FPU";
arch_defs[arch_defs_n++] = "-DLJ_ARCH_HASFPU=1";
#else
arch_defs[arch_defs_n++] = "-DLJ_ARCH_HASFPU=0";
#endif
#if LJ_ABI_SOFTFP == 1
dasm[dasm_n++] = "-D HFABI";
/* Below is strange, the logic is inverted but so it is in the luajit's makefile. */
arch_defs[arch_defs_n++] = "-DLJ_ABI_SOFTFP=0";
#else
arch_defs[arch_defs_n++] = "-DLJ_ABI_SOFTFP=1";
#endif
#if LJ_NO_UNWIND == 1
dasm[dasm_n++] = "-D NO_UNWIND";
arch_defs[arch_defs_n++] = "-DLUAJIT_NO_UNWIND";
#endif

char arm_arch_version[16];
#if LJ_ARCH_VERSION
sprintf(arm_arch_version, "-D VER=%d", LJ_ARCH_VERSION);
#else
sprintf(arm_arch_version, "-D VER=");
#endif
dasm[dasm_n++] = arm_arch_version;

#ifdef _WIN32
dasm[dasm_n++] = "-D WIN";
#endif

#if (!defined LJ_TARGET_X64 && defined LJ_TARGET_X86) && __SSE2__ == 1
dasm[dasm_n++] = "-D SSE";
#endif

printf("%s%s%s%s", lj_arch, MAIN_SEPARATOR, dasm_arch, MAIN_SEPARATOR);
for (int i = 0; i < arch_defs_n; i++) {
	printf("%s%s", i > 0 ? DEFS_SEPARATOR : "", arch_defs[i]);
}
printf(",");
for (int i = 0; i < dasm_n; i++) {
	printf("%s%s", i > 0 ? DEFS_SEPARATOR : "", dasm[i]);
}
printf("\n");

return 0;
}
