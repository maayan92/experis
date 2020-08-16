TARGET= tcpClientTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I../../inc/ -I../
INC= ../../inc/tcpClient.hpp ../../inc/socket.hpp ../testFunc.hpp
OBJS= socket.o tcpClient.o tcpClientTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

socket.o: ../../src/socket.cpp
	$(CC) $(CFLAGS) -c ../../src/socket.cpp

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp
	
tcpClientTest.o: tcpClientTest.cpp 
	$(CC) $(CFLAGS) -c tcpClientTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
