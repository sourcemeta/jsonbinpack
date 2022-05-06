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

lint:
	$(CMAKE) --build --preset $(PRESET) --target clang_tidy
.PHONY: lint

clean:
	$(CMAKE) -E rm -R -f build
.PHONY: clean

node_modules: package.json package-lock.json
	$(NPM) ci

include www/targets.mk
