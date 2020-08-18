TARGET= cdrSenderTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/cdrSender.hpp ../../inc/cdrRecord.hpp ../../inc/protocol.hpp ../../inc/tcpClient.hpp ../testFunc.hpp
OBJS= protocol.o socket.o tcpClient.o cdrSender.o cdrSenderTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

protocol.o: ../../src/protocol.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/protocol.cpp

socket.o: ../../src/socket.cpp
	$(CC) $(CFLAGS) -c ../../src/socket.cpp

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp

cdrSender.o: ../../src/cdrSender.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrSender.cpp

cdrSenderTest.o: cdrSenderTest.cpp
	$(CC) $(CFLAGS) -c cdrSenderTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
