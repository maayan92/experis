TARGET= cdrRecordTest.out 
CC= g++
CFLAGS= -ansi -pedantic -g -I../../inc/ -I../
INC= ../../inc/cdrRecord.hpp ../testFunc.hpp
OBJS= cdrRecordTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

cdrRecordTest.o: cdrRecordTest.cpp
	$(CC) $(CFLAGS) -c cdrRecordTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
