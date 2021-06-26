# User-mode access to ARMv8 PMU cycle counters

See <https://github.com/thoughtpolice/enable_arm_pmu> for details.

This repository contains a kernel module and library.

ARMv8 performance monitor units (PMUs) are only available on ARMv8 machines. In
general, this means you'll need a Cortex-A53 or better (A57, X-Gene 1, etc.)

Beware that the registers set by this module can be reset by the kernel,
such as when a core goes to sleep. For instance, on a NVidia Jetson TX1,
one need to disable idle modes by running as root:

```
for X in $(seq 0 3); do for Y in $(seq 1 6); do echo 1 > /sys/devices/system/cpu/cpu$X/cpuidle/state$Y/disable ; done ; done
```

# Testing

To compile, load, test and remove the module, you can just run:

```
$ sudo make runtests
```

## Tested on

  * Applied Micro X-C1
        Fedora 21
  * NVidia Jetson TX1
	L4T 28.1 (based on Ubuntu)
  * Odroid-C2
  	Ubuntu 18.04.02
