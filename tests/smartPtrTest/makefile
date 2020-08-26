CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../inc/ -I../../inl/
CFLAGS += -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDLIBS := -lpthread

TARGET := smartPtrTest 

OBJS := smartPtrTest.o 

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