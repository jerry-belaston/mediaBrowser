#!/bin/bash

# Visual Studio solution system builder

# Get arguments
while [ $# -gt 0 ]
do
	case "$1" in
		-fc)
			#Force cleanup of repository
			git clean -dxf .
			;;
		-h)
			#Display usage
			echo "Usage: $0 [-fc] [-h]"
			exit 0
			;;
		*)
			;;
	esac
	shift
done

#Run Cmake
build_system_generator="Visual Studio 16 2019"
build_system_platform=Win32
build_dir=_build_vs_2019_x86
source_dir=.
cmake -S "$source_dir" -B "$build_dir" -G "$build_system_generator" -A "$build_system_platform"

# Wait user action to exit
echo
read -p "Press any key to exit..."