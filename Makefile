include vendor/vendorpull/targets.mk
.DEFAULT_GOAL = all

RMRF ?= rm -rf
CMAKE ?= cmake
CTEST ?= ctest

all: preset-release
.PHONY: all

preset-%: CMakePresets.json
	$(CMAKE) --preset $(subst preset-,,$@) --log-context
	$(CMAKE) --build --preset $(subst preset-,,$@)
	$(CTEST) --preset $(subst preset-,,$@)

clean:
	$(RMRF) build
.PHONY: clean
