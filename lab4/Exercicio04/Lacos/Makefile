CC=icc
CCFLAGS=-std=c99 -O3 -qopt-report-phase=vec 

TARGET=Lacos.exe

$(TARGET):	Lacos.c
	$(CC) -o $(TARGET) $(CCFLAGS) Lacos.c

clean:
	rm -f *.o $(TARGET)
