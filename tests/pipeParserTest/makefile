TARGET= pipeParserTest.out 
CC= g++ 
CFLAGS= -ansi -pedantic -g -I../../inc/
INC= ../../inc/pipeParser.hpp ../../inc/iParser.hpp ../../inc/cdrRecord.hpp
OBJS= pipeParser.o pipeParserTest.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

pipeParser.o: ../../src/pipeParser.cpp $(INC)
	$(CC) $(CFLAGS) -c ../../src/pipeParser.cpp
	
pipeParserTest.o: pipeParserTest.cpp 
	$(CC) $(CFLAGS) -c pipeParserTest.cpp

clean:
	rm -f $(TARGET) $(OBJS)
