CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../inc/advcpp -I../../inc/advcpp/inl/ -I../../inc/ -I../inc/
CFLAGS += -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDLIBS := -lpthread

TARGET := shared_ptrTest 

OBJS := shared_ptrTest.o 

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