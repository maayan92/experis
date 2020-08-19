TARGET= main.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ 
OBJS= mutex.o mutexBucket.o main.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -pthread

mutex.o: ../../src/mutex.cpp ../../inc/mutex.hpp ../../inc/atomic.hpp
	$(CC) $(CFLAGS) -c ../../src/mutex.cpp

mutexBucket.o: ../../src/mutexBucket.cpp ../../inc/mutexBucket.hpp
	$(CC) $(CFLAGS) -c ../../src/mutexBucket.cpp

main.o: main.cpp ../../inc/uncopyable.hpp ../../inc/hashMap.hpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJS)
