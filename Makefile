ROOT := $(PWD)
include $(ROOT)/build/base.mak

SUBDIRS = startup host

STARTTIME := $(shell date +%s)
# Main targets
all: toolchain
	$(call cmd_msg,NOTICE,Build completed in $$(($$(date +%s)-$(STARTTIME))) seconds)
distclean: clean

include $(addsuffix /target.mak,$(SUBDIRS))

.PHONY: all clean distclean execute debug

toolchain: $(CC) $(LD) $(GDB)
$(CC) $(LD) $(GDB):
	$(call cmd_msg,SUBDIR,toolchain)
	$(call call_submake,toolchain,all)

execute: $(BINARY-startup)
	$(call cmd_msg,EXEC,$<)
	$(Q)$(XMD) -tcl $(ROOT)/resources/xmd_run.tcl $(QOUTPUT)

debug: $(BINARY-startup)
	$(call cmd_msg,EXECDBG,$<)
	$(call cmd_msg,NOTE,XMD starting up - attach with gdb on port 1234...)
	$(Q)$(XMD) -tcl $(ROOT)/resources/xmd_debug.tcl
