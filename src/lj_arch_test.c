#include <stdio.h>
#include "lj_arch.h"

/* Find all string used in Makefile with command

   cat Makefile | awk '/findstring .+TARGET_TESTARCH/'
*/

#define QUOTE(X) #X

int main() {

#ifdef LJ_TARGET_X64
printf("%s %d\n", QUOTE(LJ_TARGET_X64), LJ_TARGET_X64);
#endif
#ifdef LJ_TARGET_X86
printf("%s %d\n", QUOTE(LJ_TARGET_X86), LJ_TARGET_X86);
#endif
#ifdef LJ_TARGET_ARM
printf("%s %d\n", QUOTE(LJ_TARGET_ARM), LJ_TARGET_ARM);
#endif
#ifdef LJ_TARGET_PPC
printf("%s %d\n", QUOTE(LJ_TARGET_PPC), LJ_TARGET_PPC);
#endif
#ifdef LJ_TARGET_PPCSPE
printf("%s %d\n", QUOTE(LJ_TARGET_PPCSPE), LJ_TARGET_PPCSPE);
#endif
#ifdef LJ_TARGET_MIPS
printf("%s %d\n", QUOTE(LJ_TARGET_MIPS), LJ_TARGET_MIPS);
#endif
#ifdef MIPSEL
printf("%s %d\n", QUOTE(MIPSEL), MIPSEL);
#endif
#ifdef LJ_TARGET_PS3
printf("%s %d\n", QUOTE(LJ_TARGET_PS3), LJ_TARGET_PS3);
#endif
#ifdef LJ_ARCH_BITS
printf("%s %d\n", QUOTE(LJ_ARCH_BITS), LJ_ARCH_BITS);
#endif
#ifdef LJ_HASJIT
printf("%s %d\n", QUOTE(LJ_HASJIT), LJ_HASJIT);
#endif
#ifdef LJ_HASFFI
printf("%s %d\n", QUOTE(LJ_HASFFI), LJ_HASFFI);
#endif
#ifdef LJ_DUALNUM
printf("%s %d\n", QUOTE(LJ_DUALNUM), LJ_DUALNUM);
#endif
#ifdef LJ_ARCH_HASFPU
printf("%s %d\n", QUOTE(LJ_ARCH_HASFPU), LJ_ARCH_HASFPU);
#endif
#ifdef LJ_ABI_SOFTFP
printf("%s %d\n", QUOTE(LJ_ABI_SOFTFP), LJ_ABI_SOFTFP);
#endif
#ifdef LJ_NO_UNWIND
printf("%s %d\n", QUOTE(LJ_NO_UNWIND), LJ_NO_UNWIND);
#endif
#ifdef __SSE2__
printf("%s %d\n", QUOTE(__SSE2__), __SSE2__);
#endif
#ifdef LJ_ARCH_SQRT
printf("%s %d\n", QUOTE(LJ_ARCH_SQRT), LJ_ARCH_SQRT);
#endif
#ifdef LJ_ARCH_ROUND
printf("%s %d\n", QUOTE(LJ_ARCH_ROUND), LJ_ARCH_ROUND);
#endif
#ifdef LJ_ARCH_PPC64
printf("%s %d\n", QUOTE(LJ_ARCH_PPC64), LJ_ARCH_PPC64);
#endif

return 0;
}
