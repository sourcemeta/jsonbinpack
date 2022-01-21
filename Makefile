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

$(OUTPUT):
	$(MKDIR) $@

all-debug: prepare-debug compile-debug test-debug
all-release: prepare-release compile-release test-release

all: all-release

prepare-debug: | $(OUTPUT)
	$(CMAKE) -S . -B $(word 1,$|) --log-context \
		-D CMAKE_BUILD_TYPE:STRING=Debug \
		-D CMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON
prepare-release: | $(OUTPUT)
	$(CMAKE) -S . -B $(word 1,$|) --log-context \
		-D CMAKE_BUILD_TYPE:STRING=Release \
		-D CMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON

compile-debug: | $(OUTPUT)
	$(CMAKE) --build $(word 1,$|) --config Debug
compile-release: | $(OUTPUT)
	$(CMAKE) --build $(word 1,$|) --config Release

test-debug: | $(OUTPUT)
	$(CTEST) --verbose --test-dir $(word 1,$|)
test-release: | $(OUTPUT)
	$(CTEST) --verbose --test-dir $(word 1,$|)

clean:
	$(RMRF) $(OUTPUT)
