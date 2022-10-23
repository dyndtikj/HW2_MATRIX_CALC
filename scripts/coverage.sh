#!/usr/bin/env bash
set -e
TESTS="build/tests/tests"
#LIB_DIR
#cd ${BUILD_DIR} && lcov -t "testing_${LIB_DIR}" -o coverage.info -c -d ${LIB_DIR}/CMakeFiles \
#	&& lcov --remove coverage.info -o coverage.info '/usr/include/*' '/usr/lib/*' \
#	&& genhtml -o report coverage.info

lcov -t tests -o ./build/tests/coverage_report.info -c -d ./build/tests
	genhtml -o ./build/tests/coverage_report ./build/tests/coverage_report.info


#lcov -t $TESTS -o coverage.info -c
#genhtml -o build/report/ coverage.info