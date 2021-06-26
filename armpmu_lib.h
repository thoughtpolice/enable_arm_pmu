#ifndef ARMPMU_LIB_H
#define ARMPMU_LIB_H

static inline uint64_t
rdtsc64(void)
{
#if defined(__GNUC__) && defined(__aarch64__)
        uint64_t r = 0;
	asm volatile("mrs %0, PMCCNTR_EL0" : "=r"(r));
        return r;
#else
#error Unsupported architecture/compiler!
#endif
}

#endif /* ARMPMU_LIB_H */
