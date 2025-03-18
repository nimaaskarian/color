PREFIX := /usr/local

OBJ_CON := color.o contrast.o
OBJ_DRK := color.o isdark.o
OBJ_CBT := color.o colors-between.o
LDFLAGS := -lm
all: color.h contrast isdark cbetween

isdark: ${OBJ_DRK}
	${CC} -o $@ ${OBJ_DRK} ${LDFLAGS}

contrast: ${OBJ_CON}
	${CC} -o $@ ${OBJ_CON} ${LDFLAGS}

cbetween: ${OBJ_CBT}
	${CC} -o $@ ${OBJ_CBT} ${LDFLAGS}

.c.o:
	${CC} -c ${CFLAGS} $<

color.h: color.def.h color.c
	echo '#ifndef COLOR_H' > $@
	echo '#define COLOR_H' >> $@
	cat color.def.h >> $@
	grep -E '^\w+ \w+(.*)' color.c | while read -r l; do echo $$l\;; done >> $@
	echo '#endif //COLOR_H' >> $@

clean:
	rm *.o isdark contrast color.h cbetween

install: all
	cp -f contrast ${DESTDIR}${PREFIX}/bin
	cp -f isdark ${DESTDIR}${PREFIX}/bin
	cp -f cbetween ${DESTDIR}${PREFIX}/bin

uninstall:
	rm ${DESTDIR}${PREFIX}/bin/contrast
	rm ${DESTDIR}${PREFIX}/bin/isdark
	rm ${DESTDIR}${PREFIX}/bin/cbetween
