# this is my target
TARGET = test

# All .c files in this directory are my sources
SOURCES = test.cpp hash.cpp


# The compiler will be gcc("CC" is MAKE variable)
CC = g++

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
	valgrind ./$(TARGET)

.PHONY:gdb
gdb:  $(TARGET)
	gdb -q ./$(TARGET)
