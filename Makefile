include vendor/vendorpull/targets.mk
.DEFAULT_GOAL = all

CMAKE ?= cmake
CTEST ?= ctest

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
	$(CTEST) --preset $(PRESET) --verbose --tests-regex $(CASE)
else
test:
	$(CTEST) --preset $(PRESET) --verbose
endif
.PHONY: test

lint:
	$(CMAKE) --build --preset $(PRESET) --target clang_tidy
.PHONY: lint

clean:
	$(CMAKE) -E rm -R -f build
.PHONY: clean

MKDIR ?= mkdir
NPM ?= npm
NODE ?= node
INSTALL ?= install

node_modules: package.json package-lock.json
	$(NPM) ci
build:
	$(MKDIR) $@
build/www: | build
	$(MKDIR) $@
build/www/style.min.css: www/main.scss node_modules | build/www
	$(NODE) node_modules/.bin/sass $< | $(NODE) node_modules/.bin/csso > $@
build/www/%: www/% | build/www
	$(INSTALL) -m 0664 $< $@
html: \
	build/www/style.min.css \
	build/www/apple-touch-icon.png \
	build/www/benchmark-deck.png \
	build/www/example.png \
	build/www/favicon.ico \
	build/www/hybrid.png \
	build/www/icon-192x192.png \
	build/www/icon-512x512.png \
	build/www/icon.svg \
	build/www/jsonschema.png \
	build/www/manifest.webmanifest \
	build/www/index.html \
	build/www/.nojekyll \
	build/www/CNAME
.PHONY: html
