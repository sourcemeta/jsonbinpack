CMAKE = cmake
CTEST = ctest

PRESET = debug

configure: .always
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DJSONBINPACK_CLI:BOOL=ON \
		-DJSONBINPACK_TESTS:BOOL=ON \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON

compile: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_format
	$(CMAKE) --build ./build --config $(PRESET) --parallel

all: configure compile
	$(CTEST) --test-dir ./build --build-config $(PRESET) --parallel

test: configure compile
	$(CTEST) --test-dir ./build --build-config $(PRESET) --verbose --parallel

lint: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_tidy

clean: .always
	$(CMAKE) -E rm -R -f build

doxygen: configure
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

# For NMake, which doesn't support .PHONY
.always:
