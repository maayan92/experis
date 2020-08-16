TARGET= cdrFileReaderTest.out 
CC= g++
CFLAGS= -ansi -pedantic -g -I../../inc/ -I../
INC= ../../inc/cdrFileReader.hpp ../../inc/exceptions.hpp ../../inc/iParser.hpp ../../inc/pipeParser.hpp \
	../../inc/cdrSender.hpp ../../inc/socket.hpp ../../inc/tcpClient.hpp ../../inc/protocol.hpp ../testFunc.hpp
OBJS= pipeParser.o socket.o tcpClient.o cdrSender.o protocol.o cdrFileReader.o cdrFileReaderTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

pipeParser.o: ../../src/pipeParser.cpp
	$(CC) $(CFLAGS) -c ../../src/pipeParser.cpp

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp

socket.o: ../../src/socket.cpp
	$(CC) $(CFLAGS) -c ../../src/socket.cpp

cdrSender.o: ../../src/cdrSender.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrSender.cpp

protocol.o: ../../src/protocol.cpp
	$(CC) $(CFLAGS) -c ../../src/protocol.cpp

cdrFileReader.o: ../../src/cdrFileReader.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrFileReader.cpp

cdrFileReaderTest.o: cdrFileReaderTest.cpp
	$(CC) $(CFLAGS) -c cdrFileReaderTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
