TARGET= cdrRecordTest.out 
CC= g++
CFLAGS= -ansi -pedantic -g -I../../inc/
INC= ../../inc/cdrRecord.hpp
OBJS= cdrRecordTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

cdrRecordTest.o: cdrRecordTest.cpp $(INC)
	$(CC) $(CFLAGS) -c cdrRecordTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
