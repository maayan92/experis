TARGET= pipeParserTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -Wall -Werror -g -I../../inc/ -I../
INC= ../../inc/pipeParser.hpp ../../inc/iParser.hpp ../../inc/cdrRecord.hpp ../testFunc.hpp
OBJS= cdrRecord.o iParser.o pipeParser.o pipeParserTest.o

$(TARGET): $(OBJS) $(INC)
	$(CC) -o $(TARGET) $(OBJS)

cdrRecord.o: ../../src/cdrRecord.cpp
	$(CC) $(CFLAGS) -c ../../src/cdrRecord.cpp

iParser.o: ../../src/iParser.cpp
	$(CC) $(CFLAGS) -c ../../src/iParser.cpp

pipeParser.o: ../../src/pipeParser.cpp
	$(CC) $(CFLAGS) -c ../../src/pipeParser.cpp
	
pipeParserTest.o: pipeParserTest.cpp $(INC)
	$(CC) $(CFLAGS) -c pipeParserTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
