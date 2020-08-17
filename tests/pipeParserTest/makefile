TARGET= pipeParserTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/pipeParser.hpp ../../inc/iParser.hpp ../../inc/cdrRecord.hpp
OBJS= iParser.o pipeParser.o pipeParserTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS) $(INC)

iParser.o: ../../src/iParser.cpp
	$(CC) $(CFLAGS) -c ../../src/iParser.cpp

pipeParser.o: ../../src/pipeParser.cpp
	$(CC) $(CFLAGS) -c ../../src/pipeParser.cpp
	
pipeParserTest.o: pipeParserTest.cpp 
	$(CC) $(CFLAGS) -c pipeParserTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
