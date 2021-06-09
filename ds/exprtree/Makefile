# this is my target
TARGET = test

# All .c files in this directory are my sources
SOURCES = exprtree.cpp exprtree_operator.cpp exprtree_node.cpp  test.cpp

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)

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
	./$(TARGET)

valgrind:		$(TARGET)
	valgrind --leak-check=full ./$(TARGET)

.PHONY:gdb
gdb:  $(TARGET)
	gdb -q ./$(TARGET)
	
