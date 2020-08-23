TARGET= billingThreadsTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../../inl/
INC= ../../inc/mutex.hpp ../../inc/mutexBucket.hpp ../../inc/uncopyable.hpp ../../inc/hashMap.hpp ../../inc/atomic.hpp \
	../../inc/locker.hpp ../../inc/customer.hpp ../../inc/iDataAggregator.hpp ../../inc/customerBilling.hpp \
	../../inl/iDataQuery.hxx ../../inc/iDataQuery.hpp ../../inc/operator.hpp ../../inc/operatorBilling.hpp ../../inc/cdrRecord.hpp
OBJS= mutex.o mutexBucket.o cdrRecord.o iDataAggregator.o customer.o customerBilling.o operator.o operatorBilling.o billingThreadsTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -pthread

mutex.o: ../../src/mutex.cpp
	$(CC) $(CFLAGS) -c ../../src/mutex.cpp

mutexBucket.o: ../../src/mutexBucket.cpp
	$(CC) $(CFLAGS) -c ../../src/mutexBucket.cpp

cdrRecord.o: ../../src/cdrRecord.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrRecord.cpp

customer.o: ../../src/customer.cpp
	$(CC) $(CFLAGS) -c ../../src/customer.cpp

iDataAggregator.o: ../../src/iDataAggregator.cpp
	$(CC) $(CFLAGS) -c ../../src/iDataAggregator.cpp

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
