IDIR=../include
ODIR=obj
LDIR=lib
OLDIR=$(ODIR)/lib
EXE=program

CC=gcc
CFLAGS = -Wall -std=c11 -g `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0` -I$(IDIR)

WARNINGS= -Wextra -pedantic
MEMLEAK= -ggdb -fsanitize=address -fno-ommit-frame-pointer -fsanitize=undifined
DEBUG= -g -O0
OPTIMUS= -march=native -O3 -pipe -D_GNU_SOURCE

DEPS=$(IDIR)/$(wildcard *.h)
SOURCES=$(wildcard *.c)
MY_LIBS=$(wildcard $(LDIR)/*.c)
SOURCES_OBJ=$(foreach o, $(patsubst %.c,%.o,$(SOURCES)), $(ODIR)/$o)
MY_LIBS_OBJ=$(foreach o, $(patsubst %.c,%.o,$(MY_LIBS)), $(ODIR)/$o)
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`
OBJECTS= $(SOURCES_OBJ) $(MY_LIBS_OBJ)

print-% : ; @echo $* = $($*)

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

program: $(OBJECTS)
	$(CC) $(CFLAGS) $(WARNINGS) $(OPTIMUS)             $(OBJECTS) -o $(EXE)          $(LIBS)

debug: $(OBJECTS)
	$(CC) $(CFLAGS) $(WARNINGS) $(DEBUG)               $(OBJECTS) -o $(EXE).debug    $(LIBS)

memleaks: $(OBJECTS)
	$(CC) $(CFLAGS) $(WARNINGS) $(OPTIMUS) $(MEMLEAKS) $(OBJECTS) -o $(EXE).memleaks $(LIBS)

clean:
	rm obj/*.o
	rm obj/lib/*.o
	rm program*
