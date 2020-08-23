TARGET := protocolTest
CC := g++ 
CFLAGS := -ansi -pedantic -Wall -Werror
CFLAGS += -g
CPPFLAGS := -I../../inc/ -I../
CXXFLAGS := $(CFLAGS) $(CPPFLAGS) -std=c++03

INC := ../../inc/protocol.hpp ../../inc/exceptions.hpp ../../inc/cdrRecord.hpp ../testFunc.hpp
OBJS := cdrRecord.o protocol.o protocolTest.o

$(TARGET): $(OBJS)

all: $(TARGET)

cdrRecord.o: ../../src/cdrRecord.cpp
	$(CC) $(CXXFLAGS) -c ../../src/cdrRecord.cpp

protocol.o: ../../src/protocol.cpp
	$(CC) $(CXXFLAGS) -c ../../src/protocol.cpp

protocolTest.o: protocolTest.cpp $(INC)

clean:
	@$(RM) -f $(TARGET) $(OBJS)
