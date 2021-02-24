CC := $(CXX)
CXX := g++

CPPFLAGS := -I. -I../../../inc/advcpp -I../../../inc/ -I../../../tests/inc/ -I../../inc/
CPPFLAGS += -MMD -MP
CFLAGS += -Werror -Wall -Wextra
CFLAGS += -g

CXXFLAGS = $(CFLAGS) -std=c++03

LDFLAGS += $(DEBUGFLAGS)
LDLIBS := -lpthread

TARGET := agentsCreatorTest 

SRC_DIR = ../../src
SRC_DIR_ADVCPP = ../../../src
SRC_DIR_SO = ../../agents

MODULES = iObserver iPayload iSubscription iConfiguration iParser iSubscribersFinder eventTypeLocation location subscriptionHandler \
			subscriptions subscribersFinder eventsExecutor parser sensorAgentBucket \
			event sharedLibrarySo configuration fileLog agentsCreator absController absSensor

MODULES_ADVCPP = threadPool tasks mutex waitersConditionVar additionalFunctionality atomicFlag conditionVariable readersWriters

MODULES_SO = light-1-a-1 light-1-a-2 badge-reader-4-g door-4-a room-1-a-smoke room-1-a-sprinkler

PATH_MODULE = $(MODULES:%=$(SRC_DIR)/%)
PATH_MODULE_ADVCPP = $(MODULES_ADVCPP:%=$(SRC_DIR_ADVCPP)/%)
PATH_MODULE_SO = $(MODULES_SO:%=$(SRC_DIR_SO)/%)

OBJS = $(PATH_MODULE:%=%.o)
OBJS += $(PATH_MODULE_ADVCPP:%=%.o)

$(TARGET): $(OBJS) -ldl

light-1-a-1.so: CXXFLAGS += -fpic
light-1-a-1.so: LDFLAGS += -shared
light-1-a-1.so: $(SRC_DIR_SO)/light-1-a-1.o $(OBJS)
	@$(CXX) $(LDFLAGS) $(CPPFLAGS) $(SRC_DIR_SO)/light-1-a-1.o $(OBJS) $(LDLIBS) -o ./liblight-1-a-1.so

light-1-a-2.so: CXXFLAGS += -fpic
light-1-a-2.so: LDFLAGS += -shared
light-1-a-2.so: $(SRC_DIR_SO)/light-1-a-2.o $(OBJS)
	@$(CXX) $(LDFLAGS) $(CPPFLAGS) $(SRC_DIR_SO)/light-1-a-2.o $(OBJS) $(LDLIBS) -o ./liblight-1-a-2.so

badge-reader-4-g.so: CXXFLAGS += -fpic
badge-reader-4-g.so: LDFLAGS += -shared
badge-reader-4-g.so: $(SRC_DIR_SO)/badge-reader-4-g.o $(OBJS)
	@$(CXX) $(LDFLAGS) $(CPPFLAGS) $(SRC_DIR_SO)/badge-reader-4-g.o $(OBJS) $(LDLIBS) -o ./libbadge-reader-4-g.so

door-4-a.so: CXXFLAGS += -fpic
door-4-a.so: LDFLAGS += -shared
door-4-a.so: $(SRC_DIR_SO)/door-4-a.o $(OBJS)
	@$(CXX) $(LDFLAGS) $(CPPFLAGS) $(SRC_DIR_SO)/door-4-a.o $(OBJS) $(LDLIBS) -o ./libdoor-4-a.so

room-1-a-smoke.so: CXXFLAGS += -fpic
room-1-a-smoke.so: LDFLAGS += -shared
room-1-a-smoke.so: $(SRC_DIR_SO)/room-1-a-smoke.o $(OBJS)
	@$(CXX) $(LDFLAGS) $(CPPFLAGS) $(SRC_DIR_SO)/room-1-a-smoke.o $(OBJS) $(LDLIBS) -o ./libroom-1-a-smoke.so

room-1-a-sprinkler.so: CXXFLAGS += -fpic
room-1-a-sprinkler.so: LDFLAGS += -shared
room-1-a-sprinkler.so: $(SRC_DIR_SO)/room-1-a-sprinkler.o $(OBJS)
	@$(CXX) $(LDFLAGS) $(CPPFLAGS) $(SRC_DIR_SO)/room-1-a-sprinkler.o $(OBJS) $(LDLIBS) -o ./libroom-1-a-sprinkler.so

OBJ_SO = $(MODULES_SO:%=%.so)

all: $(OBJ_SO) $(TARGET)

check: all
	@clear
	./$(TARGET)
	
recheck: clean all
	@clear
	./$(TARGET)
	
VAL_ARGS = --show-leak-kinds=all
VAL_ARGS += --track-origins=yes
VAL_ARGS += --verbose
VAL_ARGS += --log-file=valgrind_out.txt

valla: $(OBJ_SO) $(TARGET)
	valgrind --leak-check=full $(VAL_ARGS) ./$(TARGET)

DRD_ARGS = --verbose
DRD_ARGS += --check-stack-var=yes
DRD_ARGS += --log-file=hellgrind_out.txt

hell: $(OBJ_SO) $(TARGET)
	valgrind --tool=drd $(DRD_ARGS) ./$(TARGET)
	./$(TARGET)

clean: 
	@$(RM) -R $(TARGET) $(OBJS) $(DEPENDS) $(DEPENDS_ADVCPP) *.so *_log.txt *.d $(DEPENDS_SO) $(PATH_MODULE_SO:%=%.o)

DEPENDS = $(PATH_MODULE:%=%.d)
DEPENDS_ADVCPP = $(PATH_MODULE_ADVCPP:%=%.d)
DEPENDS_SO = $(PATH_MODULE_SO:%=%.d)

-include $(DEPENDS) $(DEPENDS_ADVCPP)

.PHONY: all clean check recheck