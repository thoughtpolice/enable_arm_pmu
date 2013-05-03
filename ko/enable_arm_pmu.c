/*
 * Enable user-mode ARM performance counter access.
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/smp.h>

/** -- Configuration stuff ------------------------------------------------- */

#define DRVR_NAME "enable_arm_pmu"

#if !defined(__arm__)
#error Module can only be compiled on ARM machines.
#endif

/** -- Initialization & boilerplate ---------------------------------------- */

#define PERF_DEF_OPTS (1 | 16)
#define PERF_OPT_RESET_CYCLES (2 | 4)
#define PERF_OPT_DIV64 (8)

static void
enable_cpu_counters(void* data)
{
        printk(KERN_INFO "[" DRVR_NAME "] enabling user-mode PMU access on CPU #%d",
                smp_processor_id());

        /* Enable user-mode access to counters. */
        asm volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"(1));
        /* Program PMU and enable all counters */
        asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(PERF_DEF_OPTS));
        asm volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(0x8000000f));
}

static void
disable_cpu_counters(void* data)
{
        printk(KERN_INFO "[" DRVR_NAME "] disabling user-mode PMU access on CPU #%d",
                smp_processor_id());

        /* Program PMU and disable all counters */
        asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(0));
        asm volatile("mcr p15, 0, %0, c9, c12, 2" :: "r"(0x8000000f));
        /* Disable user-mode access to counters. */
        asm volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"(0));
}

static int __init
init(void)
{
        on_each_cpu(enable_cpu_counters, NULL, 1);
        printk(KERN_INFO "[" DRVR_NAME "] initialized");
        return 0;
}

static void __exit
fini(void)
{
        on_each_cpu(disable_cpu_counters, NULL, 1);
        printk(KERN_INFO "[" DRVR_NAME "] unloaded");
}

MODULE_AUTHOR("Austin Seipp <aseipp@pobox.com>");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("Enables user-mode access to ARMv7 PMU counters");
MODULE_VERSION("0:0.1-dev");
module_init(init);
module_exit(fini);
