.DEFAULT_GOAL = all

CMAKE ?= cmake
CTEST ?= ctest
BUNDLE ?= bundle

PRESET ?= debug

.PHONY: configure
configure:
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DJSONBINPACK_CLI:BOOL=ON \
		-DJSONBINPACK_TESTS:BOOL=ON \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON

.PHONY: compile
compile:
	$(CMAKE) --build ./build --config $(PRESET) --target clang_format
	$(CMAKE) --build ./build --config $(PRESET) --parallel

.PHONY: all
all: configure compile
	$(CTEST) --test-dir ./build --build-config $(PRESET) --parallel

.PHONY: test
CASE ?=
ifdef CASE
test: configure compile
	$(CTEST) --test-dir ./build --build-config $(PRESET) --verbose --tests-regex $(CASE)
else
test: configure compile
	$(CTEST) --test-dir ./build --build-config $(PRESET) --verbose
endif

.PHONY: debug
ifdef CASE
debug: scripts/lldb.sh configure compile
	./$< $(CASE)
else
debug:
	@echo "Missing CASE option" 1>&2
	exit 1
endif

.PHONY: clean
lint:
	$(CMAKE) --build ./build --config $(PRESET) --target clang_tidy

.PHONY: clean
clean:
	$(CMAKE) -E rm -R -f build .bundle .sass-cache

.PHONY: jekyll
jekyll: configure
	$(CMAKE) --build ./build --config $(PRESET) --target bundler
	$(BUNDLE) exec jekyll serve --watch --incremental --trace \
		--source www --destination build/$(PRESET)/www

.PHONY: doxygen
doxygen: configure
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen
