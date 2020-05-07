#!/bin/bash

if [[ "$#" -eq 1 && ("$1" == "--clean" || "$1" == "--rebuild") ]]; then
	rm -rf .obj bin Makefile src/.moc src/.qrc .qmake.stash
	if [ "$1" == "--clean" ]; then
		exit
	fi
elif [[ "$#" -gt 0 ]]; then
	echo "error: unrecognized argument"
	echo "usage: bash $0"
	printf "Autocompilation script\n\n"
	echo "  --clean    Remove compilation build (Makefile included)"
	echo "  --rebuild  Force target rebuild"
	exit
fi
if [[ ! -f "Makefile" ]]; then
	qmake Makefile.pro
fi
make