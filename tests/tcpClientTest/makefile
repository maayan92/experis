TARGET= tcpClientTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I../../inc/
INC= ../../inc/tcpClient.hpp ../../inc/socket.hpp
OBJS= socket.o tcpClient.o tcpClientTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

socket.o: ../../src/socket.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/socket.cpp

tcpClient.o: ../../src/tcpClient.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp
	
tcpClientTest.o: tcpClientTest.cpp 
	$(CC) $(CFLAGS) -c tcpClientTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
