OBJ := color.o contrast.o
LDFLAGS := -lm
contrast: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}
.c.o:
	${CC} -c ${CFLAGS} $<
