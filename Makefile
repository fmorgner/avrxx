# Product name
TARGET := firmware

# Platform settings
CLOCK := 16000000
MCU   := atmega328p

# Toolchain
TPREFIX := avr-
AVRSIZE := size
COMPILE := g++
OBJCOPY := objcopy
OBJDUMP := objdump

# Compiler and Linker flags
CXXFLAGS := -std=gnu++17
LDFLAGS  :=

# Project Source Directory
SRCDIR := src

# Include Directories
PINCDIRS := \
 	include
SINCDIRS := \

# Sources
SRCS := \
	main.cpp

#- DON'T EDIT BELOW HERE UNLESS YOU KNOW WHAT YOU ARE GETTING YOURSELF INTO -#

AVRSIZE := $(shell command -v $(TPREFIX)$(AVRSIZE) 2>/dev/null)
COMPILE := $(shell command -v $(TPREFIX)$(COMPILE) 2>/dev/null)
OBJCOPY := $(shell command -v $(TPREFIX)$(OBJCOPY) 2>/dev/null)
OBJDUMP := $(shell command -v $(TPREFIX)$(OBJDUMP) 2>/dev/null)

PINCDIRS := $(patsubst %,-I %,$(PINCDIRS))
SINCDIRS := $(patsubst %,-isystem %,$(SINCDIRS))

BINDIR := bin
HEXDIR := hex
OBJDIR := obj

CXXFLAGS_BASE := -g -Os -Wextra -Werror -pedantic-errors -mmcu=$(MCU) -DF_CPU=$(CLOCK) -ffunction-sections -fdata-sections
LDFLAGS_BASE  := -mmcu=$(MCU) -flto -Wl,--gc-sections

CXXFLAGS := $(CXXFLAGS_BASE) $(CXXFLAGS) $(SINCDIRS) $(PINCDIRS)
LDFLAGS  := $(LDFLAGS_BASE) $(LDFLAGS)

SRCS := $(patsubst %.cpp,$(SRCDIR)/%.cpp,$(SRCS))
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))
BINS := $(BINDIR)/$(TARGET).bin
HEXS := $(HEXDIR)/$(TARGET).hex

.PHONY: clean doc
.SECONDARY: $(OBJS) $(BINS)

#-# General Goals

all: check-tools $(HEXS)

clean:
	@$(foreach elem,$(OBJS),if [ -f $(elem) ]; then echo "RM $(elem)"; rm $(elem); fi)
	@$(foreach elem,$(DEPS),if [ -f $(elem) ]; then echo "RM $(elem)"; rm $(elem); fi)
	@$(foreach elem,$(BINS),if [ -f $(elem) ]; then echo "RM $(elem)"; rm $(elem); fi)
	@$(foreach elem,$(HEXS),if [ -f $(elem) ]; then echo "RM $(elem)"; rm $(elem); fi)
	@$(MAKE) -C doc clean

dist-clean: clean
	@if [ -d $(OBJDIR) ]; then echo "RMDIR $(OBJDIR)"; rmdir $(OBJDIR); fi
	@if [ -d $(BINDIR) ]; then echo "RMDIR $(BINDIR)"; rmdir $(BINDIR); fi
	@if [ -d $(HEXDIR) ]; then echo "RMDIR $(HEXDIR)"; rmdir $(HEXDIR); fi
	@if [ -f .tool-paths ]; then echo "RM .tool-paths"; rm .tool-paths; fi
	@if [ -d .git -a -n "$(shell git clean -xdn)" ]; then echo "GIT CLEAN"; git clean -xdf &> /dev/null; fi

#-# Documentation Goals

doc:
	@$(MAKE) -C doc html

#-# AVR Info Goals

disasm: $(BINS)
	@echo "DISASM $^"
	@$(OBJDUMP) -d $^

size: binsize hexsize

binsize: $(BINS)
	@echo "BINSIZE $^"
	@$(AVRSIZE) -C --mcu=$(MCU) $^

hexsize: $(HEXS)
	@echo "HEXSIZE $^"
	@echo "$(shell wc -c < $^) Bytes"

#-# File Pattern Goals

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@echo "COMPILE $@"
	@$(COMPILE) $(CXXFLAGS) -MMD -MP -c -o $@ $<

-include $(OBJDIR)/*.d

$(BINDIR)/%.bin: $(OBJS) | $(BINDIR)
	@echo "LINK $@"
	@$(COMPILE) $(LDFLAGS) -o $@ $^

$(HEXDIR)/%.hex: $(BINS) | $(HEXDIR)
	@echo "OBJCOPY $@"
	@$(OBJCOPY) -j .text -j .data -O ihex $^ $@

#-# Directory Goals

$(OBJDIR):
	@echo "MKDIR $@"
	@mkdir -p $@

$(BINDIR):
	@echo "MKDIR $@"
	@mkdir -p $@

$(HEXDIR):
	@echo "MKDIR $@"
	@mkdir -p $@

#-# Toolchain Checking Goals

check-tools: .tool-paths

check-compiler:
ifndef COMPILE
	@$(error "No suitable compiler found!")
endif

check-linker: check-compiler

check-objcopy:
ifndef OBJCOPY
	@$(error "No suitable objcopy found!")
endif

check-disasm:
ifndef OBJDUMP
	@$(error "No suitable disassembler found!")
endif

check-binsize:
ifndef AVRSIZE
	@$(error "No suitable size calculator found!")
endif

.tool-paths: | check-compiler check-linker check-objcopy check-disasm check-binsize
	@echo "g++     : $(COMPILE)" | tee -a .tool-paths
	@echo "objcopy : $(OBJCOPY)" | tee -a .tool-paths
	@echo "objdump : $(OBJDUMP)" | tee -a .tool-paths
	@echo "avrsize : $(AVRSIZE)" | tee -a .tool-paths
