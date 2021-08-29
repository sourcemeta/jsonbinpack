include vendor/vendorpull/targets.mk
.DEFAULT_GOAL = all
.PHONY: all prepare compile lint format test clean

#################################################
# Variables
#################################################

OUTPUT ?= build

#################################################
# Files
#################################################

CPP_SOURCES = jsonbinpack/**/*.cc test/**/*.cc test/*.cc
CPP_HEADERS = jsonbinpack/**/*.h

#################################################
# Programs
#################################################

MKDIR ?= mkdir
RMRF ?= rm -rf
CMAKE ?= cmake
CTEST ?= ctest

#################################################
# Targets
#################################################

$(OUTPUT):
	$(MKDIR) $@

all: prepare lint compile test

prepare: | $(OUTPUT)
	$(CMAKE) -S . -B $(word 1,$|) -D CMAKE_EXPORT_COMPILE_COMMANDS=ON

compile: | $(OUTPUT)
	$(CMAKE) --build $(word 1,$|)

test: | $(OUTPUT)
	$(CTEST) --verbose --test-dir $(word 1,$|)

clean:
	$(RMRF) $(OUTPUT)
