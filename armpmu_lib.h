#ifndef ARMPMU_LIB_H
#define ARMPMU_LIB_H

static inline uint32_t
rdtsc32(void)
{
#if defined(__GNUC__) && defined(__ARM_ARCH_7A__)
        uint32_t r = 0;
        asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r) );
        return r;
#else
#error Unsupported architecture/compiler!
#endif
}

// Ho-Ren(Jack) Chuang
static inline uint64_t 
rdtscll(void)
{
#if defined(CONFIG_ARM64)
    uint64_t val = 0;
    asm volatile("msr cntv_ctl_el0,  %0" : : "r" (val));
    return val;
#else
#error Unsupported architecture/compiler!
#endif
}

#endif /* ARMPMU_LIB_H */
