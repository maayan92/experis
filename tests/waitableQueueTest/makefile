CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../inc/advcpp -I../../inc/ -I../inc/
CFLAGS += -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDLIBS := -lpthread

TARGET := waitableQueueTest

OBJS := waitableQueueTest.o ../../src/mutex.o ../../src/atomicFlag.o ../../src/conditionVariable.o

$(TARGET): $(OBJS)

all: $(TARGET)

check: $(TARGET) 	
	@clear
	./$(TARGET)

recheck: clean all
	@clear
	./$(TARGET)

VAL_ARGS = --show-leak-kinds=all
VAL_ARGS += --track-origins=yes
VAL_ARGS += --verbose
VAL_ARGS += --log-file=valgrind_out.txt

valla: $(TARGET)
	valgrind --leak-check=full $(VAL_ARGS) ./$(TARGET)

DRD_ARGS = --verbose
DRD_ARGS += --check-stack-var=yes

hell: $(TARGET)
	valgrind --tool=helgrind
	./$(TARGET)

clean: 
	@$(RM) -f $(TARGET) $(OBJS)

.PHONY: all clean check recheck