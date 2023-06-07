CMAKE = cmake
CTEST = ctest

PRESET = debug

all: .always
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET) --parallel
	$(CTEST) --preset $(PRESET) --parallel

test: .always
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target clang_format
	$(CMAKE) --build --preset $(PRESET) --parallel
	$(CTEST) --preset $(PRESET) --verbose --parallel

clean: .always
	$(CMAKE) -E rm -R -f build

doxygen: .always
	$(CMAKE) --preset $(PRESET) --log-context
	$(CMAKE) --build --preset $(PRESET) --target doxygen

# For NMake, which doesn't support .PHONY
.always:
