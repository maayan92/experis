CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../../inc/advcpp -I../../../inc/ -I../../../tests/inc/ -I../../inc/  -I../inc/
CPPFLAGS += -MMD -MP
CFLAGS += -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDLIBS := -lpthread

TARGET := eventsExecutorTest 

SRC_DIR = ../../src
SRC_DIR_ADVCPP = ../../../src

MODULES = iObserver iPayload iSubscription controllerTest eventTypeLocation \
			location subscriptionHandler subscriptions iSubscribersFinder iObserversNotifier \
			subscribersFinder observersNotifierMT eventsExecutor event notifyingTask fileLog

MODULES_ADVCPP = threadPool tasks mutex waitersConditionVar additionalFunctionality atomicFlag conditionVariable readersWriters

PATH_MODULE = $(MODULES:%=$(SRC_DIR)/%)
PATH_MODULE_ADVCPP = $(MODULES_ADVCPP:%=$(SRC_DIR_ADVCPP)/%)

OBJS = $(PATH_MODULE:%=%.o)
OBJS += $(PATH_MODULE_ADVCPP:%=%.o)

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
	@$(RM) -f $(TARGET) $(OBJS) $(DEPENDS) $(DEPENDS_ADVCPP) *.d *_log.txt

DEPENDS = $(PATH_MODULE:%=%.d)
DEPENDS_ADVCPP = $(PATH_MODULE_ADVCPP:%=%.d)
-include $(DEPENDS) $(DEPENDS_ADVCPP)

.PHONY: all clean check recheck