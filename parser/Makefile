# this is my target
TARGET = kuku_test

# All .c files in this directory are my sources
SOURCES = kuku_test.cpp Parser.cpp Tokenizer.cpp Analyzer.cpp

# Include directory
INC_DIR = ../include/
# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CPPFLAGS = -ansi -pedantic -Werror -Wall -g3

#for pre-procees compiletime
CPPFLAGS += -I$(INC_DIR)
#linkerflags
LDFLAGS= -g


#  my objects are the .o of my sources
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY:all
all: $(TARGET)

# The default command, compile all the sources
#$(CC) $(LDFLAGS) $(^) -o $(@)

$(TARGET): $(OBJECTS)  

#built-in c compiler rule is $(CC) $(CFLAGS) $(CPPFLAGS) -c  -o $(@) $(<)

#spacial targets
.PHONY:clean
clean:
	rm -f $(TARGET) *.o *.out *.txt

.PHONY:run
run: $(TARGET)
	./$(TARGET) 11_Parser_qq

valgrind:		$(TARGET)
	valgrind ./$(TARGET)

.PHONY:gdb
gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
