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
HUGO ?= hugo

node_modules: package.json package-lock.json
	$(NPM) ci

build:
	$(MKDIR) $@
build/www: | build
	$(MKDIR) $@
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

html: build/www/style.min.css
	$(HUGO) --source $(realpath www) --destination $(realpath build/www)
.PHONY: html
serve: build/www/style.min.css
	$(HUGO) serve --source $(realpath www) --destination $(realpath build/www)
.PHONY: serve
