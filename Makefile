OBJ_CON := color.o contrast.o
OBJ_DRK := color.o isdark.o
LDFLAGS := -lm
all: contrast isdark

isdark: ${OBJ_DRK}
	${CC} -o $@ ${OBJ_DRK} ${LDFLAGS}

contrast: ${OBJ_CON}
	${CC} -o $@ ${OBJ_CON} ${LDFLAGS}

.c.o:
	${CC} -c ${CFLAGS} $<

install: all
	cp -f contrast ${DESTDIR}${PREFIX}/bin
	cp -f isdark ${DESTDIR}${PREFIX}/bin
