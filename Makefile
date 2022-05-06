include vendor/vendorpull/targets.mk
.DEFAULT_GOAL = all

CMAKE ?= cmake
CTEST ?= ctest
NPM ?= npm

PRESET ?= debug
all:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET)
	$(CTEST) --preset $(PRESET)
.PHONY: all

CASE ?=
ifdef CASE
test:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET)
	$(CTEST) --preset $(PRESET) --verbose --tests-regex $(CASE)
else
test:
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET)
	$(CTEST) --preset $(PRESET) --verbose
endif
.PHONY: test

ifdef CASE
debug: scripts/lldb.sh
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET)
	./$< $(PRESET) $(CASE)
else
debug:
	@echo "Missing CASE option" 1>&2
	exit 1
endif
.PHONY: debug

clean:
	$(CMAKE) -E rm -R -f build
.PHONY: clean

node_modules: package.json package-lock.json
	$(NPM) ci

include www/targets.mk
