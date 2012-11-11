# Target file name.
TARGET = host

# List C source files here.
CCSOURCES = main.c

# List C++ source files here.
CXXSOURCES = 

# List Assembler to be assembled here
GASSOURCES = 

# C compiler flags
CFLAGS  = -std=gnu99 -ggdb -O0 
CFLAGS += -Wall 

# C++ compiler flags
CXXFLAGS  = 

# GAS flags
GASFLAGS = 

# Linker flags
LDFLAGS = 

# Additional include paths to consider
INCLUDES = 

# Additional local static libs to link against
LIBS = 

# Folder for object files
OBJDIR = obj

# Folder for sourcecode
SRCDIR = src

# Additional defines
DEFINES := 

include $(ROOT)/build/host-executable.mak
