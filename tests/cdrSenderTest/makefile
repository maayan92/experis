TARGET= cdrSenderTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/cdrSender.hpp ../../inc/cdrRecord.hpp ../../inc/protocol.hpp ../../inc/tcpClient.hpp
OBJS= protocol.o cdrRecord.o tcpClient.o cdrSender.o cdrSenderTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

protocol.o: ../../src/protocol.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/protocol.cpp

cdrRecord.o: ../../src/cdrRecord.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrRecord.cpp

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp

cdrSender.o: ../../src/cdrSender.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrSender.cpp

cdrSenderTest.o: cdrSenderTest.cpp
	$(CC) $(CFLAGS) -c cdrSenderTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
