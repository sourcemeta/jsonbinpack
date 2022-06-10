MKDIR ?= mkdir
INSTALL ?= install

build:
	$(MKDIR) $@
build/www: | build
	$(MKDIR) $@
build/www/%: www/% | build/www
	$(INSTALL) -m 0664 $< $@
html: \
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
	$(CMAKE) --build --preset $(PRESET) --target website
	$(CMAKE) --build --preset $(PRESET) --target doxygen
.PHONY: html
