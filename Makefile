DEMO_DIR = build/hw1_matrix_main
TESTS_DIR = build/tests/tests

.PHONY: all build rebuild check test coverage clean

all: clean check build test

build: clean
	scripts/build.sh

test:
	scripts/build.sh -DBUILD_TESTS=ON
	./${TESTS_DIR}

rebuild: clean build

check:
	scripts/checks.sh

run: build
	./${DEMO_DIR}

coverage: build
	scripts/coverage.sh ./${TESTS_DIR}


clean:
	rm -rf build/