/** compile with -std=gnu99 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>

static int fddev = -1;
__attribute__((constructor)) static void
init(void)
{
	static struct perf_event_attr attr;
	attr.type = PERF_TYPE_HARDWARE;
	attr.config = PERF_COUNT_HW_CPU_CYCLES;
	fddev = syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
}

__attribute__((destructor)) static void
fini(void)
{
	close(fddev);
}

static inline long long
cpucycles(void)
{
	long long result = 0;
	if (read(fddev, &result, sizeof(result)) < sizeof(result)) return 0;
	return result;
}

/* Simple loop body to keep things interested. Make sure it gets inlined. */
static inline int
loop(int* __restrict__ a, int* __restrict__ b, int n)
{
        unsigned sum = 0;
        for (int i = 0; i < n; ++i)
                if(a[i] > b[i])
                        sum += a[i] + 5;
        return sum;
}

int
main(int ac, char **av)
{
        long long time_start = 0;
        long long time_end   = 0;

        int *a  = NULL;
        int *b  = NULL;
        int len = 0; 
	int sum = 0;

        if (ac != 2) return -1;
        len = atoi(av[1]);
	printf("%s: len = %d\n", av[0], len);

        a = malloc(len*sizeof(*a));
        b = malloc(len*sizeof(*b));

        for (int i = 0; i < len; ++i) {
                a[i] = i+128;
                b[i] = i+64;
        }

        printf("%s: beginning loop\n", av[0]);
        time_start = cpucycles();
        sum = loop(a, b, len);
        time_end   = cpucycles();
        printf("%s: done. sum = %d; time delta = %llu\n", av[0], sum, time_end - time_start);

        free(a); free(b);
        return 0;
}
