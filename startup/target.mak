# Target file name.
TARGET = startup

# List C source files here.
CCSOURCES = vectors.c \
			main.c \
			Drivers/io.c \
			Newlib/_sbrk.c \
			Newlib/_exit.c \
			Newlib/_write.c \
			Newlib/_read.c \
			Newlib/newlib_stubs.c \
			ps7_init.c \
			Drivers/uart.c

# List C++ source files here.
CXXSOURCES = 

# List Assembler to be assembled here
GASSOURCES = Startup/vectortable.S \
				Startup/boot.S \
				Startup/crt0.S \
				Startup/translation_tables.S

# C compiler flags
CFLAGS  = -std=gnu99 -ggdb -O0 -march=armv7-a -mtune=cortex-a9 -mfpu=neon -ftree-vectorize -ffast-math -mfloat-abi=softfp
CFLAGS += -Wall 

# C++ compiler flags
CXXFLAGS  = 

# GAS flags
GASFLAGS = -march=armv7-a -mtune=cortex-a9 -mfpu=neon -ftree-vectorize -ffast-math -mfloat-abi=softfp

# Linker flags
# we need crti and crtn for _init() and _fini()
EXTRAOBJECTS := $(shell $(CC) -print-file-name=crti.o) \
				$(shell $(CC) -print-file-name=crtn.o)
LDFLAGS := -Wl,-T$(ROOT)/startup/linker.ld,-Map,$(ROOT)/startup/startup.map -nostartfiles $(EXTRAOBJECTS)

# Additional include paths to consider
INCLUDES = $(ROOT)/startup/inc

# Additional local static libs to link against
LIBS = 

# Folder for object files
OBJDIR = obj

# Folder for sourcecode
SRCDIR = src

# Additional defines
DEFINES := 

include $(ROOT)/build/executable.mak
