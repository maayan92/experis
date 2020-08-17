TARGET= serverTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/tcpServer.hpp ../../inc/exceptions.hpp ../../inc/tcpClient.hpp \
		../../inc/protocol.hpp ../../inc/serverManager.hpp ../../inc/reciever.hpp ../testFunc.hpp
OBJS= tcpServer.o tcpClient.o protocol.o serverManager.o serverTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp

protocol.o: ../../src/protocol.cpp
	$(CC) $(CFLAGS) -c ../../src/protocol.cpp

tcpServer.o: ../../src/tcpServer.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpServer.cpp

serverManager.o: ../../src/serverManager.cpp
	$(CC) $(CFLAGS) -c ../../src/serverManager.cpp

serverTest.o: serverTest.cpp
	$(CC) $(CFLAGS) -c serverTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
