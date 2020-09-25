CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../../inc/advcpp -I../../../inc/ -I../../../tests/inc/ -I../../inc/  -I../inc/ -I../../observers/
CPPFLAGS += -MMD -MP
CFLAGS += -pedantic -pedantic-errors -ansi -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDFLAGS += $(DEBUGFLAGS)
LDLIBS := -lpthread

TARGET := sharedLibrarySoTest 

SRC_DIR = ../../src
SRC_DIR_ADVCPP = ../../../src
SRC_DIR_SO = ../../observers

MODULES = iObserver iPayload iSubscription eventTypeLocation eventsExecutor sharedLibrarySo
MODULES += location subscriptionHandler subscriptions iSubscribersFinder iObserversNotifier
MODULES += subscribersFinder observersNotifierMT

MODULES_ADVCPP = threadPool tasks mutex waitersConditionVar additionalFunctionality atomicFlag conditionVariable readersWriters

PATH_MODULE = $(MODULES:%=$(SRC_DIR)/%)
PATH_MODULE_ADVCPP = $(MODULES_ADVCPP:%=$(SRC_DIR_ADVCPP)/%)

OBJS = $(PATH_MODULE:%=%.o)
OBJS += $(PATH_MODULE_ADVCPP:%=%.o)

$(TARGET): LDLIBS += -ldl
$(TARGET): $(OBJS)

ControllerHVAC.so: CXXFLAGS += -fpic
ControllerHVAC.so: LDFLAGS += -shared
ControllerHVAC.so: clean $(OBJS)
#@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRC_DIR_SO)/controllerHVAC.o $(LDLIBS) -o $(SRC_DIR_SO)/libControllerHVAC.so

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
	@$(RM) -f $(TARGET) $(OBJS) $(DEPENDS) $(DEPENDS_ADVCPP)

DEPENDS = $(PATH_MODULE:%=%.d)
DEPENDS_ADVCPP = $(PATH_MODULE_ADVCPP:%=%.d)
-include $(DEPENDS) $(DEPENDS_ADVCPP)

.PHONY: all clean check recheck