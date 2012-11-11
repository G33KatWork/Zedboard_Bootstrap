ROOT := ..
include $(ROOT)/build/base.mak

TOOLCHAIN_BUILDDIR  := $(TOOLCHAIN_ROOTDIR)/build-tmp

#detect cpus
CPUS ?= $(shell ./detect_cpus.sh)
SUBMAKEFLAGS := -j$(CPUS)

all: info

include $(ROOT)/toolchain/binutils.mak
include $(ROOT)/toolchain/gcc-newlib.mak
include $(ROOT)/toolchain/gdb.mak

STARTTIME := $(shell date +%s)
all:
	$(call cmd_msg,INFO,Build completed in $$(($$(date +%s)-$(STARTTIME))) seconds)
	$(call cmd_msg,INFO,Execute a >>make clean<< to remove build tempfiles)

info:
	$(call cmd_msg,INFO,Using $(CPUS) threads)

clean:
	$(Q)if [ -n "$(TOOLCHAIN_BUILDDIR)" -a -d "$(TOOLCHAIN_BUILDDIR)" ]; then \
		rm -rf $(TOOLCHAIN_BUILDDIR); \
	fi

distclean: clean
	$(Q)if [ -n "$(TOOLCHAIN_SRCDIR)" -a -d "$(TOOLCHAIN_SRCDIR)" ]; then \
		rm -rf $(TOOLCHAIN_SRCDIR); \
	fi

toolchain-clean: clean
	$(Q)if [ -n "$(TOOLCHAIN_ROOTDIR)" -a -d "$(TOOLCHAIN_ROOTDIR)" ]; then \
		rm -rf $(TOOLCHAIN_ROOTDIR); \
	fi

.PHONY: info download clean distclean toolchain-clean
.DEFAULT_GOAL = all
