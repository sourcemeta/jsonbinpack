MKDIR ?= mkdir
INSTALL ?= install
CONVERT ?= convert

build:
	$(MKDIR) $@
build/$(PRESET): | build
	$(MKDIR) $@
build/$(PRESET)/www: | build/$(PRESET)
	$(MKDIR) $@
build/$(PRESET)/www/%: www/% | build/$(PRESET)/www
	$(INSTALL) -m 0664 $< $@

build/$(PRESET)/www/icon-%.png: build/$(PRESET)/www/icon.svg | build/$(PRESET)/www
	$(CONVERT) +antialias -background transparent -resize $(basename $(subst icon-,,$(notdir $@))) $< $@
build/$(PRESET)/www/apple-touch-icon.png: build/$(PRESET)/www/icon.svg | build/$(PRESET)/www
	$(CONVERT) +antialias -background transparent -resize 180x180 $< $@
build/$(PRESET)/www/favicon.ico: build/$(PRESET)/www/icon.svg | build/$(PRESET)/www
	$(CONVERT) +antialias -resize 32x32 $< $@

html: node_modules \
	build/$(PRESET)/www/apple-touch-icon.png \
	build/$(PRESET)/www/benchmark-deck.png \
	build/$(PRESET)/www/example.png \
	build/$(PRESET)/www/favicon.ico \
	build/$(PRESET)/www/hybrid.png \
	build/$(PRESET)/www/icon-192x192.png \
	build/$(PRESET)/www/icon-512x512.png \
	build/$(PRESET)/www/icon.svg \
	build/$(PRESET)/www/jsonschema.png \
	build/$(PRESET)/www/manifest.webmanifest \
	build/$(PRESET)/www/index.html \
	build/$(PRESET)/www/404.html \
	build/$(PRESET)/www/.nojekyll \
	build/$(PRESET)/www/CNAME
	$(CMAKE) --build --preset $(PRESET) --target website
	$(CMAKE) --build --preset $(PRESET) --target doxygen
.PHONY: html
