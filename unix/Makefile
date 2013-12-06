MACSTL_DIR = ../

CC = g++

ifeq ($(shell uname -m | grep -o ppc), ppc)
PLATFORM = PPC
else 
ifeq ($(shell uname -m | grep -o 86), 86)
PLATFORM = x86
endif
endif

ifeq ($(PLATFORM), PPC)
COMMON_OPT = -maltivec -O3 -static -lstdc++ -lm
else
ifeq ($(PLATFORM), x86)
COMMON_OPT = -march=pentium4 -mfpmath=sse -O3 -static -lstdc++ -lm
endif
endif

all : benchmark mmaptest vectest

benchmark : ../test/benchmark.cpp common.h
	$(CC) $(COMMON_OPT) -fno-unit-at-time -I$(MACSTL_DIR) $< -o $@

mmaptest : ../test/mmaptest.cpp
	$(CC) $(COMMON_OPT) -I$(MACSTL_DIR) $< -o $@

vectest : ../test/vectest.cpp common.h
	$(CC) $(COMMON_OPT) -I$(MACSTL_DIR) $< -o $@

common.h : 

clean :
	rm -f benchmark mmaptest vectest
