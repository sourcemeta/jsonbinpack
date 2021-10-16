include vendor/vendorpull/targets.mk

OUTPUT_DIRECTORY ?= out

$(OUTPUT_DIRECTORY):
	mkdir -p $@

.DEFAULT_GOAL = build
.PHONY: all prepare build lint format test clean

all: prepare build test

CPP_SOURCES = jsonbinpack/**/*.cc test/**/*.cc test/*.cc
CPP_HEADERS = jsonbinpack/**/*.h

prepare: | $(OUTPUT_DIRECTORY)
	cmake -S . -B $(word 1,$|) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: | $(OUTPUT_DIRECTORY)
	cmake --build $(word 1,$|)

lint:
	shellcheck configure .github/*.sh
	python2 vendor/styleguide/cpplint/cpplint.py $(CPP_SOURCES) $(CPP_HEADERS)
	clang-tidy -p $(OUTPUT_DIRECTORY) --checks='' --warnings-as-errors='' $(CPP_SOURCES) $(CPP_HEADERS)

format:
	clang-format -i $(CPP_SOURCES) $(CPP_HEADERS)

test: | $(OUTPUT_DIRECTORY)
	ctest --verbose --test-dir $(word 1,$|)

clean:
	rm -rf $(OUTPUT_DIRECTORY) Testing
