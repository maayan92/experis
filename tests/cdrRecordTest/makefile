TARGET= cdrRecordTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
OBJS= cdrRecord.o cdrRecordTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

cdrRecord.o: ../../src/cdrRecord.cpp ../../inc/cdrRecord.hpp
	$(CC) $(CFLAGS) -c ../../src/cdrRecord.cpp

cdrRecordTest.o: cdrRecordTest.cpp
	$(CC) $(CFLAGS) -c cdrRecordTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
