TARGET= tcpClientTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/tcpClient.hpp ../testFunc.hpp
OBJS= tcpClient.o tcpClientTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp
	
tcpClientTest.o: tcpClientTest.cpp $(INC)
	$(CC) $(CFLAGS) -c tcpClientTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
