TARGET= cdrFileReaderTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/cdrFileReader.hpp ../../inc/exceptions.hpp ../../inc/iParser.hpp ../../inc/pipeParser.hpp \
	../../inc/cdrRecord.hpp ../../inc/cdrSender.hpp ../../inc/tcpClient.hpp ../../inc/protocol.hpp ../testFunc.hpp
OBJS= iParser.o pipeParser.o cdrRecord.o tcpClient.o cdrSender.o protocol.o cdrFileReader.o cdrFileReaderTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

iParser.o: ../../src/iParser.cpp
	$(CC) $(CFLAGS) -c ../../src/iParser.cpp

pipeParser.o: ../../src/pipeParser.cpp
	$(CC) $(CFLAGS) -c ../../src/pipeParser.cpp

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp

cdrRecord.o: ../../src/cdrRecord.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrRecord.cpp

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
