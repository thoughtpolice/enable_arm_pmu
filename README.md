# User-mode access to ARM PMU cycle counters

This repository contains a kernel module and library.

ARM performance monitor units (PMUs) are only available on ARMv7 machines. In
general, this means you'll need a Cortex-A7 or better (A8, A9, A15, etc.)

More details are available in [my blog post][blog].

[blog]: http://neocontra.blogspot.com/2013/05/user-mode-performance-counters-for.html

# Testing

To compile, load, test and remove the module, you can just run:

```
$ sudo make runtests
```

## Tested on

  * Samsung Chromebook
    * Exynos 5 Dual, 1.7gHz Cortex-A15
    * Ubuntu 13.04
  * ODROID-U2
    * Exynos 4 Quad, 1.7gHz Cortex-A9
    * Ubuntu/Linaro 12.10 derivative

TBD: PandaBoard.

# Join in

Be sure to read the [contributing guidelines][contribute]. File bugs
in the GitHub [issue tracker][].

Master [git repository][gh]:

* `git clone https://github.com/thoughtpolice/enable_arm_pmu.git`

There's also a [BitBucket mirror][bb]:

* `git clone https://bitbucket.org/thoughtpolice/enable_arm_pmu.git`

# Authors

See [AUTHORS.txt](https://raw.github.com/thoughtpolice/enable_arm_pmu/master/AUTHORS.txt).

# License

MIT. See
[LICENSE.txt](https://raw.github.com/thoughtpolice/enable_arm_pmu/master/LICENSE.txt)
for terms of copyright and redistribution.

[contribute]: https://github.com/thoughtpolice/enable_arm_pmu/blob/master/CONTRIBUTING.md
[issue tracker]: http://github.com/thoughtpolice/enable_arm_pmu/issues
[gh]: http://github.com/thoughtpolice/enable_arm_pmu
[bb]: http://bitbucket.org/thoughtpolice/enable_arm_pmu
