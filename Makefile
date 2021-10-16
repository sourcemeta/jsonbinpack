include vendor/vendorpull/targets.mk

OUTPUT_DIRECTORY ?= out

$(OUTPUT_DIRECTORY):
	mkdir -p $@

.DEFAULT_GOAL = build
.PHONY: all prepare build lint format test clean

all: prepare build test

CPP_SOURCES = jsonbinpack/**/*.cc jsonbinpack/**/*.h
CPP_HEADERS = jsonbinpack/**/*.h

prepare: | $(OUTPUT_DIRECTORY)
	cmake -S . -B $(word 1,$|)

build: | $(OUTPUT_DIRECTORY)
	cmake --build $(word 1,$|)

lint:
	shellcheck configure .github/*.sh
	python2 vendor/styleguide/cpplint/cpplint.py $(CPP_SOURCES) $(CPP_HEADERS)

format:
	clang-format -i $(CPP_SOURCES) $(CPP_HEADERS)

test: | $(OUTPUT_DIRECTORY)
	ctest --verbose --test-dir $(word 1,$|)

clean:
	rm -rf $(OUTPUT_DIRECTORY) Testing
