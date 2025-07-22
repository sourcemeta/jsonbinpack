# Programs
CMAKE = cmake
CTEST = ctest
PYTHON = python3

# Options
PRESET = Debug
SHARED = OFF

all: configure compile test

configure: .always
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON \
		-DJSONBINPACK_NUMERIC:BOOL=ON \
		-DJSONBINPACK_RUNTIME:BOOL=ON \
		-DJSONBINPACK_COMPILER:BOOL=ON \
		-DJSONBINPACK_TESTS:BOOL=ON \
		-DJSONBINPACK_DOCS:BOOL=ON \
		-DBUILD_SHARED_LIBS:BOOL=$(SHARED)

compile: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_format
	$(CMAKE) --build ./build --config $(PRESET) --parallel 4
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_core
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_core_dev
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsonbinpack
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsonbinpack_dev

test: .always
	$(CMAKE) -E env UBSAN_OPTIONS=print_stacktrace=1 \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--output-on-failure --progress --parallel

doxygen: .always
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

clean: .always
	$(CMAKE) -E rm -R -f build

# For NMake, which doesn't support .PHONY
.always:
