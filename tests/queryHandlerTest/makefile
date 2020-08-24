CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../inc/ -I../../inl/ -I../
CFLAGS += -Werror -Wall -Wextra 
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03 

LDLIBS := -lpthread

TARGET := queryHandlerTest

OBJS := queryHandlerTest.o ../../src/mutex.o ../../src/mutexBucket.o ../../src/cdrRecord.o ../../src/iDataAggregator.o \
		../../src/customer.o ../../src/customerBilling.o ../../src/operator.o ../../src/operatorBilling.o \
		../../src/queryHandler.o

$(TARGET): $(OBJS)

all: $(TARGET)

check: $(TARGET) 
	@clear
	./$(TARGET)

recheck: clean all
	@clear
	./$(TARGET)

clean:
	@$(RM) -f $(TARGET) $(OBJS)

.PHONY: all clean check recheck