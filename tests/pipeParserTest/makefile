TARGET= pipeParserTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/pipeParser.hpp ../../inc/iParser.hpp ../../inc/cdrRecord.hpp ../testFunc.hpp
OBJS= pipeParser.o pipeParserTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

pipeParser.o: ../../src/pipeParser.cpp
	$(CC) $(CFLAGS) -c ../../src/pipeParser.cpp
	
pipeParserTest.o: pipeParserTest.cpp 
	$(CC) $(CFLAGS) -c pipeParserTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
