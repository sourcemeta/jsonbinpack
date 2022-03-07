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
INSTALL ?= install
TOUCH ?= touch
CONVERT ?= convert
NPM ?= npm
NODE ?= node

node_modules: package.json package-lock.json
	$(NPM) ci

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

build/www/style.min.css: www/less/style.less node_modules \
	www/less/_backgrounds.less \
	www/less/_config.less \
	www/less/_general.less \
	www/less/_grid.less \
	www/less/_layout.less \
	www/less/_list.less \
	www/less/_media.less \
	www/less/_mixins.less \
	www/less/_text.less \
	www/less/modules/_pe-icon-7-stroke.less \
	www/less/modules/_logo.less \
	www/less/modules/_header-back.less \
	www/less/modules/_header.less \
	www/less/modules/_footer.less \
	www/less/modules/_menu.less \
	www/less/modules/_page-info.less \
	www/less/modules/_promo-title.less \
	www/less/modules/_box.less \
	www/less/modules/_faq.less \
	www/less/modules/_call-to-action.less | build/www
	$(NODE) node_modules/less/bin/lessc --compress $< > $@

build/www/fonts: | build/www
	$(MKDIR) $@
build/www/fonts/%: www/fonts/% | build/www/fonts
	$(INSTALL) -m 0664 $< $@
build/www/images: | build/www
	$(MKDIR) $@
build/www/images/background-secondary.png: assets/background-secondary.png | build/www/images
	$(INSTALL) -m 0664 $< $@
build/www/images/%: www/images/% | build/www/images
	$(INSTALL) -m 0664 $< $@
build/www/logo.png: assets/logo.png | build/www
	$(INSTALL) -m 0664 $< $@
build/www/example@2x.png: assets/example@2x.png | build/www
	$(INSTALL) -m 0664 $< $@
build/www/example.png: assets/example.png | build/www
	$(INSTALL) -m 0664 $< $@
build/www/.nojekyll: | build/www
	$(TOUCH) $@

build/www/stats.html: www/stats.html | build/www
	$(INSTALL) -m 0664 $< $@
build/www/stats: | build/www
	$(MKDIR) $@
build/www/stats/index.html: www/stats.html | build/www/stats
	$(INSTALL) -m 0664 $< $@
build/www/index.html: www/index.html build/www/style.min.css \
	build/www/manifest.webmanifest build/www/icon.svg build/www/favicon.ico build/www/apple-touch-icon.png \
	build/www/logo.png \
	build/www/example.png \
	build/www/example@2x.png \
	build/www/images/jumbotron.jpg \
	build/www/images/background-secondary.png \
	build/www/fonts/Pe-icon-7-stroke.eot \
	build/www/fonts/Pe-icon-7-stroke.svg \
	build/www/fonts/Pe-icon-7-stroke.ttf \
	build/www/fonts/Pe-icon-7-stroke.woff
	$(INSTALL) -m 0664 $< $@

html: build/www/index.html build/www/stats.html build/www/stats/index.html \
	build/www/CNAME build/www/.nojekyll
.PHONY: html
