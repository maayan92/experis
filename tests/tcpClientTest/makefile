TARGET= tcpClientTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/tcpClient.hpp
OBJS= tcpClient.o tcpClientTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

tcpClient.o: ../../src/tcpClient.cpp
	$(CC) $(CFLAGS) -c ../../src/tcpClient.cpp
	
tcpClientTest.o: tcpClientTest.cpp 
	$(CC) $(CFLAGS) -c tcpClientTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
