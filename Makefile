CMAKE = cmake
CTEST = ctest

PRESET = debug
GENERATOR = Ninja Multi-Config

all: .always
	$(CMAKE) --preset $(PRESET) --log-context -G "$(GENERATOR)"
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET)
	$(CTEST) --preset $(PRESET)

test: .always
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET)
	$(CTEST) --preset $(PRESET) --verbose

clean: .always
	$(CMAKE) -E rm -R -f build

doxygen: .always
	$(CMAKE) --preset $(PRESET) --log-context -G "$(GENERATOR)"
	$(CMAKE) --build --preset $(PRESET) --target doxygen

# For NMake, which doesn't support .PHONY
.always:
