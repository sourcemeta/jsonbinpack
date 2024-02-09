# Programs
CMAKE = cmake
CTEST = ctest

# Options
PRESET = Debug
SHARED = OFF

all: configure compile test

configure: .always
	$(CMAKE) -S . -B ./build \
		-DCMAKE_BUILD_TYPE:STRING=$(PRESET) \
		-DCMAKE_COMPILE_WARNING_AS_ERROR:BOOL=ON \
		-DJSONBINPACK_CLI:BOOL=ON \
		-DJSONBINPACK_RUNTIME:BOOL=ON \
		-DJSONBINPACK_COMPILER:BOOL=ON \
		-DJSONBINPACK_TESTS:BOOL=ON \
		-DJSONBINPACK_WEBSITE:BOOL=ON \
		-DBUILD_SHARED_LIBS:BOOL=$(SHARED)

compile: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_format
	$(CMAKE) --build ./build --config $(PRESET) --parallel 4
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsonbinpack
	$(CMAKE) --install ./build --prefix ./build/dist --config $(PRESET) --verbose \
		--component sourcemeta_jsonbinpack_dev

lint: .always
	$(CMAKE) --build ./build --config $(PRESET) --target clang_tidy

test: .always
	$(CMAKE) -E env UBSAN_OPTIONS=print_stacktrace=1 \
		$(CTEST) --test-dir ./build --build-config $(PRESET) \
			--output-on-failure --progress --parallel

website: .always
	$(CMAKE) --build ./build --config $(PRESET) --target bundler
	$(CMAKE) --build ./build --config $(PRESET) --target jekyll
	$(CMAKE) --build ./build --config $(PRESET) --target doxygen

clean: .always
	$(CMAKE) -E rm -R -f build

# For NMake, which doesn't support .PHONY
.always:
