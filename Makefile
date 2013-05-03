all: ko/enable_arm_pmu.ko perf_arm_pmu perf_event_open
perf_arm_pmu: perf_arm_pmu.c
	@echo CC perf_arm_pmu
	@$(CC) -O3 -std=gnu99 perf_arm_pmu.c -o perf_arm_pmu 
perf_event_open: perf_event_open.c
	@echo CC perf_event_open 
	@$(CC) -O3 -std=gnu99 perf_event_open.c -o perf_event_open 
ko/enable_arm_pmu.ko: ko/enable_arm_pmu.c
	@echo KMOD ko/enable_arm_pmu.ko
	@$(MAKE) -C ko > /dev/null
runtests: all
	@echo SUDO load-module
	@./load-module
	@./perf_arm_pmu 64 
	@./perf_event_open 64 
	@echo SUDO unload-module
	@./unload-module

clean:
	@($(MAKE) -C ko clean > /dev/null) && rm -f perf_arm_pmu perf_event_open *.o *~
