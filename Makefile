include vendor/vendorpull/targets.mk
.DEFAULT_GOAL = all
.PHONY: all all-debug all-release \
	prepare-debug prepare-release \
	compile-debug compile-release lint \
	test-debug test-release clean

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

all-debug: prepare-debug compile-debug test-debug
all-release: prepare-release compile-release test-release

all: all-release

prepare-debug: CMakePresets.json
	$(CMAKE) --preset debug --log-context
prepare-release: CMakePresets.json
	$(CMAKE) --preset release --log-context

compile-debug: CMakePresets.json
	$(CMAKE) --build --preset debug
compile-release: CMakePresets.json
	$(CMAKE) --build --preset release

test-debug: CMakePresets.json
	$(CTEST) --preset debug
test-release: CMakePresets.json
	$(CTEST) --preset release

clean:
	$(RMRF) $(OUTPUT)
