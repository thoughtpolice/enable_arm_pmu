# User-mode access to ARMv8 PMU cycle counters

See <https://github.com/thoughtpolice/enable_arm_pmu> for details.

This repository contains a kernel module and library.

ARMv8 performance monitor units (PMUs) are only available on ARMv8 machines. In
general, this means you'll need a Cortex-A53 or better (A57, X-Gene 1, etc.)

# Testing

To compile, load, test and remove the module, you can just run:

```
$ sudo make runtests
```

## Tested on

  * Applied Micro X-C1
        Fedora 21
