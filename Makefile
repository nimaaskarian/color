PREFIX  := /usr/local
CFLAGS   =  -std=c++23 -pedantic -Wall -Wno-unused-function -Wno-deprecated-declarations -O3 $(shell pkg-config --cflags opencv4)
LDFLAGS := -lm $(shell pkg-config --libs opencv4)

BIN := contrast isdark cbetween as-rgb  isimgdark
CC := g++

all: .gitignore color.h color.o ${BIN}

${BI}: %: %.o
	${CC} -o $@ color.opp $< ${LDFLAGS}

$(BIN): %: %.o
	${CC} -o $@ color.o $< ${LDFLAGS}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

color.h: color.def.h color.c
	echo '#ifndef COLOR_H' > $@
	echo '#define COLOR_H' >> $@
	cat color.def.h >> $@
	grep -E '^\w+ \w+(.*)' color.c | while read -r l; do echo $$l\;; done >> $@
	echo '#endif //COLOR_H' >> $@

.gitignore: Makefile
	echo \*.o > $@
	echo ${BIN} | tr ' ' '\n' >> $@

clean:
	rm *.o *.opp ${BIN} ${BIN_CPP}

install: all
	$(foreach bin, ${BIN}, cp -f $(bin) ${DESTDIR}${PREFIX}/bin;)

uninstall:
	$(foreach bin, ${BIN}, rm ${DESTDIR}${PREFIX}/bin/$(bin);)
