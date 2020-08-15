TARGET= protocolTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I../../inc/
INC= ../../inc/protocol.hpp ../../inc/cdrRecord.hpp
OBJS= protocol.o protocolTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

protocol.o: ../../src/protocol.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/protocol.cpp

protocolTest.o: protocolTest.cpp $(INC)
	$(CC) $(CFLAGS) -c protocolTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
