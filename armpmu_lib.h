#ifndef ARMPMU_LIB_H
#define ARMPMU_LIB_H

static inline uint32_t
rdtsc32(void)
{
#if defined(__GNUC__)
        uint32_t r = 0;
#if  defined __aarch64__     
	asm volatile("mrs %0, pmccntr_el0" : "=r" (r)); 
#elif defined(__ARM_ARCH_7A__)
        asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r) );
#else
#error Unsupported architecture/compiler!
#endif
        return r;
#endif
}

#endif /* ARMPMU_LIB_H */
