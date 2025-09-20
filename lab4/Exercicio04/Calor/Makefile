COMP=-c

CC=icc
CC_WALL_TIME_FLAGS=-O3 -qopt-report-phase=vec 
CCFLAGS=-std=c99 $(CC_WALL_TIME_FLAGS) 
CCLOAD=$(CCFLAGS)

EXEC=Calor.exe

OBJ=Calor.o \
    wall_time.o

all:	$(EXEC)


$(EXEC):	$(OBJ)
	$(CC) -o $(EXEC) $(CCLOAD) $(OBJ)

wall_time.o: wall_time.c
	$(CC) $(COMP) $(CC_WALL_TIME_FLAGS) wall_time.c

Calor.o: Calor.c
	$(CC) $(COMP) $(CCFLAGS) Calor.c

clean:
	rm -f *.o $(EXEC) 




