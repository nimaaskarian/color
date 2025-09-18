PREFIX  := /usr/local
IMGLIBS := -lopencv_core -lopencv_imgcodecs
IMGINCS     = $(shell pkg-config --cflags opencv4)
LIBS    := -lm
CFLAGS  := -std=c++23 -pedantic -Wall -Wno-unused-function -Wno-deprecated-declarations -O3
LDFLAGS := ${LIBS}

BIN := contrast isdark cbetween as-rgb isimgdark
CC := g++

all: .gitignore color.h color.o ${BIN}

$(BIN): %: %.o
	${CC} -o $@ color.o $< ${LDFLAGS}

isimgdark: isimgdark.o
	${CC} -o $@ color.o $< ${IMGLIBS}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

isimgdark.o: isimgdark.cpp
	$(CC) $(CFLAGS) $(IMGINCS) -c $< -o $@

color.h: color.def.h color.c
	echo '#ifndef COLOR_H' > $@
	echo '#define COLOR_H' >> $@
	echo '#ifdef __cplusplus' >> $@
	echo 'extern "C" {' >>  $@
	echo '#endif' >> $@
	cat color.def.h >> $@
	grep -E '^\w+ \w+(.*)' color.c | while read -r l; do echo $$l\;; done >> $@
	echo '#endif //COLOR_H' >> $@
	echo '#ifdef __cplusplus' >> $@
	echo '}' >> $@
	echo '#endif' >> $@

.gitignore: Makefile
	echo \*.o > $@
	echo ${BIN} | tr ' ' '\n' >> $@

.PHONY: clean
clean:
	rm -f *.o ${BIN} || return 0

install: all
	$(foreach bin, ${BIN}, cp -f $(bin) ${DESTDIR}${PREFIX}/bin;)

uninstall:
	$(foreach bin, ${BIN}, rm ${DESTDIR}${PREFIX}/bin/$(bin);)
