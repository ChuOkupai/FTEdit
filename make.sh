#!/bin/bash

if [[ ("$#" -eq 1) && ("$1" == "--clean") ]]; then
	rm -rf bin Makefile .moc .obj .qmake.stash
	exit
elif [ "$#" -gt 0 ]; then
	echo "error: unrecognized argument"
	echo "usage: bash $0"
	printf "Autocompilation script\n\n"
	echo "  --clean  Remove compilation build (Makefile included)"
	exit
fi
if [ ! -f "Makefile" ]; then
	qmake Makefile.pro
fi
make