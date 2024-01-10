# Programs
CMAKE = cmake
CTEST = ctest

# Options
PRESET = Debug

all: configure compile test

configure: .always
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DJSONBINPACK_CLI:BOOL=ON \
		-DJSONBINPACK_TESTS:BOOL=ON \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON

compile: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_format
	$(CMAKE) --build ./build --config $(PRESET) --parallel 4
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsonbinpack
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsonbinpack_dev

test: .always
	$(CTEST) --test-dir ./build --build-config $(PRESET) \
		--output-on-failure --progress --parallel

lint: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_tidy

clean: .always
	$(CMAKE) -E rm -R -f build

doxygen:
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

# For NMake, which doesn't support .PHONY
.always:
