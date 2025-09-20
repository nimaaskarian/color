PREFIX  := /usr/local
IMGLIBS := $(shell pkg-config --libs opencv4) $(shell pkg-config --libs tbb)
IMGINCS  = $(shell pkg-config --cflags opencv4)
LIBS    := -lm
CFLAGS  := -std=c++20 -pedantic -Wall -Wno-unused-function -Wno-deprecated-declarations -O3
LDFLAGS := ${LIBS}

BIN_CPP := isimgdark wal
BIN := contrast isdark gradient as-rgb
CC := g++
OBJ_CPP := ${BIN_CPP:=.o}

all: .gitignore color.h color.o ${BIN} ${BIN_CPP}

$(BIN): %: %.o
	${CC} -o $@ color.o $< ${LDFLAGS}

${BIN_CPP}: %: %.o
	${CC} -o $@ color.o $< ${IMGLIBS}

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

${OBJ_CPP}: %.o: %.cpp
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
	printf "%s\n" ${BIN} ${BIN_CPP} >> $@

.PHONY: clean
clean:
	rm -f *.o ${BIN} || return 0

install: all
	$(foreach bin, ${BIN}, cp -f $(bin) ${DESTDIR}${PREFIX}/bin;)

uninstall:
	$(foreach bin, ${BIN}, rm ${DESTDIR}${PREFIX}/bin/$(bin);)
