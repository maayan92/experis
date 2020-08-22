TARGET= billingThreadsTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/
INC= ../../inc/mutex.hpp ../../inc/mutexBucket.hpp ../../inc/uncopyable.hpp ../../inc/hashMap.hpp ../../inc/atomic.hpp \
	../../inc/locker.hpp ../../inc/customer.hpp ../../inc/iDataAggregator.hpp ../../inc/customerBilling.hpp \
	../../inc/operator.hpp ../../inc/operatorBilling.hpp
OBJS= mutex.o mutexBucket.o customer.o customerBilling.o operator.o operatorBilling.o billingThreadsTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -pthread

mutex.o: ../../src/mutex.cpp
	$(CC) $(CFLAGS) -c ../../src/mutex.cpp

mutexBucket.o: ../../src/mutexBucket.cpp
	$(CC) $(CFLAGS) -c ../../src/mutexBucket.cpp

customer.o: ../../src/customer.cpp
	$(CC) $(CFLAGS) -c ../../src/customer.cpp

customerBilling.o: ../../src/customerBilling.cpp
	$(CC) $(CFLAGS) -c ../../src/customerBilling.cpp

operator.o: ../../src/operator.cpp
	$(CC) $(CFLAGS) -c ../../src/operator.cpp

operatorBilling.o: ../../src/operatorBilling.cpp
	$(CC) $(CFLAGS) -c ../../src/operatorBilling.cpp

billingThreadsTest.o: billingThreadsTest.cpp $(INC)
	$(CC) $(CFLAGS) -c billingThreadsTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
