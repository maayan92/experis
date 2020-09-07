CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../inc/advcpp -I../../inc/ -I../inc/
CFLAGS += -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDLIBS := -lpthread

TARGET := threadPoolTest

OBJS := threadPoolTest.o ../../src/mutex.o ../../src/atomicFlag.o ../../src/conditionVariable.o ../../src/waitersConditionVar.o \
		../../src/tasks.o ../../src/threadPool.o

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
DRD_ARGS += --log-file=hellgrind_out.txt

hell: $(TARGET)
	valgrind --tool=drd $(DRD_ARGS) ./$(TARGET)
	./$(TARGET)

clean: 
	@$(RM) -f $(TARGET) $(OBJS)

.PHONY: all clean check recheck