.DEFAULT_GOAL = all

CMAKE ?= cmake
CTEST ?= ctest
BUNDLE ?= bundle

PRESET ?= debug

.PHONY: all
all:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET) --parallel
	$(CTEST) --preset $(PRESET) --parallel

.PHONY: test
CASE ?=
ifdef CASE
test:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET) --parallel
	$(CTEST) --preset $(PRESET) --verbose --tests-regex $(CASE)
else
test:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET) --parallel
	$(CTEST) --preset $(PRESET) --verbose
endif

.PHONY: debug
ifdef CASE
debug: scripts/lldb.sh
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --parallel
	./$< $(PRESET) $(CASE)
else
debug:
	@echo "Missing CASE option" 1>&2
	exit 1
endif

.PHONY: clean
clean:
	$(CMAKE) -E rm -R -f build .bundle .sass-cache

.PHONY: jekyll
jekyll:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target bundler
	$(BUNDLE) exec jekyll serve --watch --incremental --trace \
		--source www --destination build/$(PRESET)/www

.PHONY: doxygen
doxygen:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target doxygen
