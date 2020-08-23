TARGET= protocolTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/protocol.hpp ../../inc/exceptions.hpp ../../inc/cdrRecord.hpp
OBJS= testFunc.o protocol.o protocolTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

testFunc.o: ../testFunc.cpp $(INC)
	$(CC) $(CFLAGS) -c ../testFunc.cpp

protocol.o: ../../src/protocol.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/protocol.cpp

protocolTest.o: protocolTest.cpp $(INC)
	$(CC) $(CFLAGS) -c protocolTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
