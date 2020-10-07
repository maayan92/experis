CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../tests/inc/
CPPFLAGS += -MMD -MP
CFLAGS += -Werror -Wall -Wextra -pedantic -ansi
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03 -std=gnu++11

LDLIBS := -lpthread

TARGET := day2Test 

MODULES = findSpecificElement firstDuplicateT

OBJS = $(MODULES:%=%.o)

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
	@$(RM) -f $(TARGET) $(OBJS) $(DEPENDS) *.d 

DEPENDS = $(PATH_MODULE:%=%.d)
-include $(DEPENDS)

.PHONY: all clean check recheck