PREFIX  := /usr/local
INCS     = $(shell pkg-config --cflags opencv4)
LIBS    := -lm -lopencv_core -lopencv_imgcodecs
CFLAGS  := -std=c++23 -pedantic -Wall -Wno-unused-function -Wno-deprecated-declarations -O3 ${INCS}
LDFLAGS := ${LIBS}

BIN := contrast isdark cbetween as-rgb  isimgdark
CC := g++

all: .gitignore color.h color.o ${BIN}

$(BIN): %: %.o
	${CC} -o $@ color.o $< ${LDFLAGS}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

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
	rm *.o ${BIN} || return 0

install: all
	$(foreach bin, ${BIN}, cp -f $(bin) ${DESTDIR}${PREFIX}/bin;)

uninstall:
	$(foreach bin, ${BIN}, rm ${DESTDIR}${PREFIX}/bin/$(bin);)
