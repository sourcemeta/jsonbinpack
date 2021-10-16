include vendor/vendorpull/targets.mk

OUTPUT_DIRECTORY ?= out

$(OUTPUT_DIRECTORY):
	mkdir -p $@

.DEFAULT_GOAL = build
.PHONY: all prepare build lint format test clean

all: prepare build test

prepare: | $(OUTPUT_DIRECTORY)
	cmake -S . -B $(word 1,$|)

build: | $(OUTPUT_DIRECTORY)
	cmake --build $(word 1,$|)

lint:
	shellcheck configure .github/*.sh
	python2 vendor/styleguide/cpplint/cpplint.py \
		jsonbinpack/**/*.cc \
		jsonbinpack/**/*.h \
		test/**/*.cc

format:
	clang-format -i \
		jsonbinpack/**/*.cc \
		jsonbinpack/**/*.h \
		test/**/*.cc

test: | $(OUTPUT_DIRECTORY)
	ctest --verbose --test-dir $(word 1,$|)

clean:
	rm -rf $(OUTPUT_DIRECTORY) Testing
