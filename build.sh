#!/usr/bin/bash

# Change to build dir
user=$(whoami)
BUILD_DIR="${PWD}/build"
mkdir $BUILD_DIR || exit 1
cd $BUILD_DIR || exit 1

# Argument parsing
while [[ $# -gt 0 ]]; do
	key="$1"
	case $key in
		-d | --debug)
			build_debug=1
			shift;;
		-c | --clear)
			clear_build_dir=1
			shift;;
		-t | --test)
			build_tests=1
			shift;;
		'')
			;;
		*)
			echo "Usage: $0 [options]"
			echo "  -c (--clear) - Clear the output directory before building"
			echo "                   Does not clear any eventual ccache entries"
			echo "  -d (--debug) - Build debug version, default is Release"
			echo "  -t (--test)  - Also build test program"
			exit
			;;
	esac
done

# Clear build if requested
if [ $clear_build_dir ]; then
	echo "Clearing the output directory .."
	rm -r $BUILD_DIR/* || exit 1
fi

# Choose build type
if [ $build_debug ]; then build_type="Debug"
else build_type="Release"; fi

# Build
cmake -DCMAKE_BUILD_TYPE=$build_type -DBUILD_TESTS=$build_tests .. || exit 1
make || exit 1
