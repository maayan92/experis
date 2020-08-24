TARGET= serverTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/tcpServer.hpp ../../inc/exceptions.hpp ../../inc/tcpClient.hpp ../../inc/cdrRecord.hpp\
		../../inc/protocol.hpp ../testFunc.hpp
OBJS= cdrRecord.o tcpServer.o tcpClient.o protocol.o serverTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp

cdrRecord.o: ../../src/cdrRecord.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrRecord.cpp

protocol.o: ../../src/protocol.cpp
	$(CC) $(CFLAGS) -c ../../src/protocol.cpp

tcpServer.o: ../../src/tcpServer.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpServer.cpp

serverTest.o: serverTest.cpp
	$(CC) $(CFLAGS) -c serverTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
