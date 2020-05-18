NAME := FTEdit
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	BIN = ./release/$(NAME)
	DEPLOY = linuxdeployqt
	DEPLOY_TARGET = ./release/$(NAME)
endif
ifeq ($(UNAME_S),Darwin)
	BIN = release/$(NAME).app
	DEPLOY = macdeployqt
	DEPLOY_TARGET = release/$(NAME).dmg
	MKBUILD = \
	ln -s ~/Applications ./release/Applications && \
	hdiutil create -fs HFS+ -srcfolder ./release -volname "$(NAME)" "$(DEPLOY_TARGET)"
endif

all: src/Makefile
	make -C src

src/Makefile:
	cd src && qmake Makefile.pro

release/$(DEPLOY_TARGET): all
	$(DEPLOY) $(BIN)
	$(MKBUILD)

deploy: release/$(DEPLOY_TARGET)

clean:
	rm -rf .build release src/Makefile .qmake.stash
