TARGET= customerBillingTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../../inl/
INC= ../../inc/mutex.hpp ../../inc/mutexBucket.hpp ../../inc/uncopyable.hpp ../../inc/hashMap.hpp ../../inc/atomic.hpp \
	../../inc/locker.hpp ../../inc/customer.hpp ../../inc/iDataAggregator.hpp ../../inl/iDataQuery.hxx \
	../../inc/iDataQuery.hpp ../../inc/cdrRecord.hpp ../../inc/customerBilling.hpp
OBJS= mutex.o mutexBucket.o cdrRecord.o iDataAggregator.o customer.o customerBilling.o customerBillingTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -pthread

mutex.o: ../../src/mutex.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/mutex.cpp

mutexBucket.o: ../../src/mutexBucket.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/mutexBucket.cpp

cdrRecord.o: ../../src/cdrRecord.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/cdrRecord.cpp

iDataAggregator.o: ../../src/iDataAggregator.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/iDataAggregator.cpp

customer.o: ../../src/customer.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/customer.cpp

customerBilling.o: ../../src/customerBilling.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/customerBilling.cpp

customerBillingTest.o: customerBillingTest.cpp $(INC)
	$(CC) $(CFLAGS) -c customerBillingTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
