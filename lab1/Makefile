COMP=-c

CC=gcc
CCFLAGS= 
CCLOAD= $(CCFLAGS)

EXEC=Tempo.exe

OBJ=\
	wall_time.o \
	ModVida.o \
        Tempo.o

all:	$(EXEC)


$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(CCLOAD) $(OBJ)

Tempo.o:	Tempo.c ModVida.o wall_time.o

clean:
	rm -f *.o $(EXEC)


.SUFFIXES	:	.o .c

.c.o:
	$(CC) $(COMP) $(CCFLAGS) $*.c 



