include vendor/vendorpull/targets.mk

CPP_SOURCES = jsonbinpack/**/*.cc test/**/*.cc test/*.cc
CPP_HEADERS = jsonbinpack/**/*.h
OUTPUT_DIRECTORY ?= out

$(OUTPUT_DIRECTORY):
	mkdir -p $@

.DEFAULT_GOAL = build
.PHONY: all prepare build lint format test clean web

#################################################
# Phony targets
#################################################

all: prepare build test web

prepare: | $(OUTPUT_DIRECTORY)
	cmake -S . -B $(word 1,$|) -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: | $(OUTPUT_DIRECTORY)
	cmake --build $(word 1,$|)

lint:
	python2 vendor/styleguide/cpplint/cpplint.py $(CPP_SOURCES) $(CPP_HEADERS)
	clang-tidy -p $(OUTPUT_DIRECTORY) --checks='' --warnings-as-errors='' $(CPP_SOURCES) $(CPP_HEADERS)
	shellcheck bin/jsonbinpack

format:
	clang-format -i $(CPP_SOURCES) $(CPP_HEADERS)

test: | $(OUTPUT_DIRECTORY)
	ctest --verbose --test-dir $(word 1,$|)

clean:
	rm -rf $(OUTPUT_DIRECTORY) Testing

web: \
	docs/css/style.min.css \
	docs/logo.png \
	docs/apple-touch-icon-114x114.png \
	docs/apple-touch-icon-120x120.png \
	docs/apple-touch-icon-144x144.png \
	docs/apple-touch-icon-152x152.png \
	docs/apple-touch-icon-180x180.png \
	docs/apple-touch-icon-57x57.png \
	docs/apple-touch-icon-60x60.png \
	docs/apple-touch-icon-72x72.png \
	docs/apple-touch-icon-76x76.png \
	docs/favicon-16x16.png \
	docs/favicon-32x32.png \
	docs/favicon-96x96.png

#################################################
# Website
#################################################

docs/css/style.min.css: www/less/style.less \
	$(wildcard www/less/global/*.less) \
	$(wildcard www/less/libs/*.less) \
	$(wildcard www/less/modules/*.less)
	./node_modules/.bin/lessc --compress --js $< $@

docs/logo.png: assets/logo.png
	cp $< $@

docs/apple-touch-icon-%.png: docs/logo.png
	convert -strip -resize $(basename $(subst apple-touch-icon-,,$(notdir $@))) $< $@

docs/favicon-%.png: docs/logo.png
	convert -strip -resize $(basename $(subst favicon-,,$(notdir $@))) $< $@
