PREFIX  := /usr/local
CFLAGS   = -std=c99 -pedantic -Wall -Wno-unused-function -Wno-deprecated-declarations -O3
LDFLAGS := -lm

BIN := contrast isdark cbetween as-rgb


all: .gitignore color.h color.o ${BIN}

$(BIN): %: %.o
	${CC} -o $@ color.o $< ${LDFLAGS}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

color.h: color.def.h color.c
	echo '#ifndef COLOR_H' > $@
	echo '#define COLOR_H' >> $@
	cat color.def.h >> $@
	grep -E '^\w+ \w+(.*)' color.c | while read -r l; do echo $$l\;; done >> $@
	echo '#endif //COLOR_H' >> $@

.gitignore: Makefile
	echo \*.o > $@
	for bin in ${BIN}; do \
		echo $$bin >> $@; \
	done

clean:
	rm *.o ${BIN}

install: all
	cp -f contrast ${DESTDIR}${PREFIX}/bin
	cp -f isdark ${DESTDIR}${PREFIX}/bin
	cp -f cbetween ${DESTDIR}${PREFIX}/bin

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/contrast
	rm ${DESTDIR}${PREFIX}/bin/isdark
	rm ${DESTDIR}${PREFIX}/bin/cbetween
