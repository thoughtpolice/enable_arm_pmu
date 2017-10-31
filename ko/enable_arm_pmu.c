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

// ARMv7-A Architecture Reference Manual B4.1.26
#define CNTKCTL_PL0VCTEN 0x2

static void
enable_cpu_counters(void* data)
{
        uint32_t r;

        printk(KERN_INFO "[" DRVR_NAME "] enabling user-mode PMU access on CPU #%d",
                smp_processor_id());

        /* Enable user-mode access to counters. */
        asm volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"(1));
        /* Program PMU and enable all counters */
        asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(PERF_DEF_OPTS));
        asm volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(0x8000000f));

        /* Enable user-mode access to CNTVCT generic timer counter in co-processor CP15 */
        asm volatile("mrc p15, 0, %0, c14, c1, 0" : "=r"(r)); /* Read CNTKCTL to Rt */
        r |= CNTKCTL_PL0VCTEN;
        asm volatile("mcr p15, 0, %0, c14, c1, 0" :: "r"(r)); /* Write Rt to CNTKCTL */
}

static void
disable_cpu_counters(void* data)
{
        uint32_t r;

        printk(KERN_INFO "[" DRVR_NAME "] disabling user-mode PMU access on CPU #%d",
                smp_processor_id());

        /* Program PMU and disable all counters */
        asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(0));
        asm volatile("mcr p15, 0, %0, c9, c12, 2" :: "r"(0x8000000f));
        /* Disable user-mode access to counters. */
        asm volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"(0));

        /* Disable user-mode access to CNTVCT generic timer counter in co-processor CP15 */
        asm volatile("mrc p15, 0, %0, c14, c1, 0" : "=r"(r)); /* Read CNTKCTL to Rt */
        r &= ~CNTKCTL_PL0VCTEN;
        asm volatile("mcr p15, 0, %0, c14, c1, 0" :: "r"(r)); /* Write Rt to CNTKCTL */
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
MODULE_DESCRIPTION("Enables user-mode access to cycle counters in PMU and CNTVCT timer on ARMv7");
MODULE_VERSION("0:0.1-dev");
module_init(init);
module_exit(fini);
