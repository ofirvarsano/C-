# this is my target
TARGET = main

# All .c files in this directory are my sources
SOURCES = main.cpp memManager_t.cpp memPage_t.cpp memPool_t.cpp

# The compiler will be gcc("CC" is MAKE variable)
CC = g++ 
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CPPFLAGS = -ansi -pedantic -Werror -Wall -g3

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
	rm -f $(TARGET) *.o *.out

.PHONY:run
run: $(TARGET)
	./$(TARGET) -v

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY:gdb
gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	  
