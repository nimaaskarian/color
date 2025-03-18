OBJ := color.o contrast.o
LDFLAGS := -lm
all: contrast

contrast: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

.c.o:
	${CC} -c ${CFLAGS} $<

install: all
	cp -f contrast ${DESTDIR}${PREFIX}/bin
