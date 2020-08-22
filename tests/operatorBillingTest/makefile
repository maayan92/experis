TARGET= operatorBillingTest.out 
CC= g++
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/
INC= ../../inc/mutex.hpp ../../inc/mutexBucket.hpp ../../inc/uncopyable.hpp ../../inc/hashMap.hpp ../../inc/atomic.hpp \
	../../inc/locker.hpp ../../inc/operator.hpp ../../inc/iDataAggregator.hpp ../../inc/operatorBilling.hpp
OBJS= mutex.o mutexBucket.o operator.o operatorBilling.o operatorBillingTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -pthread

mutex.o: ../../src/mutex.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/mutex.cpp

mutexBucket.o: ../../src/mutexBucket.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/mutexBucket.cpp

operator.o: ../../src/operator.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/operator.cpp

operatorBilling.o: ../../src/operatorBilling.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/operatorBilling.cpp

operatorBillingTest.o: operatorBillingTest.cpp $(INC)
	$(CC) $(CFLAGS) -c operatorBillingTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
