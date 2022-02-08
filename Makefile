include vendor/vendorpull/targets.mk
.DEFAULT_GOAL = all

CMAKE ?= cmake
CTEST ?= ctest

all: preset-release
.PHONY: all

preset-%: CMakePresets.json
	$(CMAKE) --preset $(subst preset-,,$@) --log-context
	$(CMAKE) --build --preset $(subst preset-,,$@)
	$(CTEST) --preset $(subst preset-,,$@)

clean:
	$(CMAKE) -E rm -R build
.PHONY: clean

MKDIR ?= mkdir
INSTALL ?= install
CONVERT ?= convert

build:
	$(MKDIR) $@
build/www: | build
	$(MKDIR) $@
build/www/icon-%.png: assets/favicon.png | build/www
	$(CONVERT) -resize $(basename $(notdir $(subst icon-,,$@))) $< $@
build/www/apple-touch-icon.png: build/www/icon-180x180.png
	$(INSTALL) -m 0664 $< $@
build/www/icon.svg: assets/favicon.svg | build/www
	$(INSTALL) -m 0664 $< $@
build/www/favicon.ico: build/www/icon-32x32.png
	$(CONVERT) $^ $@
build/www/manifest.webmanifest: www/manifest.webmanifest build/www/icon-192x192.png build/www/icon-512x512.png
	$(INSTALL) -m 0664 $< $@
build/www/CNAME: www/CNAME
	$(INSTALL) -m 0664 $< $@
build/www/index.html: www/index.html \
	build/www/manifest.webmanifest build/www/icon.svg build/www/favicon.ico build/www/apple-touch-icon.png
	$(INSTALL) -m 0664 $< $@

html: build/www/index.html build/www/CNAME
.PHONY: html

