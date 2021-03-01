CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../../inc/advcpp -I../../../inc/ -I../../../tests/inc/ -I../../inc/  -I../inc/ -I../../observers/
CPPFLAGS += -MMD -MP
CFLAGS += -ansi -pedantic -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDLIBS := -lpthread

TARGET := messageHandlerTest 

SRC_DIR = ../../src
SRC_DIR_ADVCPP = ../../../src
SRC_DIR_SENSOR = ../../observers

MODULES = iObserver iPayload eventTypeLocation location sensorAgentBucket iEventCreator \
			eventCreatorMT event messageHandler messageSeparator iMessageHandler protocol fileLog absSensor

MODULES_ADVCPP = mutex waitersConditionVar conditionVariable atomicFlag threadPool tasks

MODULES_SENSOR = temperatureSensor

PATH_MODULE = $(MODULES:%=$(SRC_DIR)/%)
PATH_MODULE_ADVCPP = $(MODULES_ADVCPP:%=$(SRC_DIR_ADVCPP)/%)
PATH_MODULE_SENSOR = $(MODULES_SENSOR:%=$(SRC_DIR_SENSOR)/%)

OBJS = $(PATH_MODULE:%=%.o)
OBJS += $(PATH_MODULE_ADVCPP:%=%.o)
OBJS += $(PATH_MODULE_SENSOR:%=%.o)

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
	@$(RM) -f $(TARGET) $(OBJS) $(DEPENDS) $(DEPENDS_ADVCPP) $(DEPENDS_SENSOR) *_log.txt *.d

DEPENDS = $(PATH_MODULE:%=%.d)
DEPENDS_ADVCPP = $(PATH_MODULE_ADVCPP:%=%.d)
DEPENDS_SENSOR = $(PATH_MODULE_SENSOR:%=%.d)
-include $(DEPENDS) $(DEPENDS_ADVCPP)

.PHONY: all clean check recheck