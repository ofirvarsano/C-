# this is my target
TARGET = cyc_blking_queue_test

# All .c files in this directory are my sources
SOURCES = cyc_blking_queue_test.cpp cyc_blking_queque.cpp ../../threads/mutex.cpp ../../threads/semaphore.cpp condition_variable.cpp

# The compiler will be gcc("CC" is MAKE variable)
CC = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CPPFLAGS = -ansi -pedantic -g3

#linkerflags
LDFLAGS= -g -pthread

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
	rm -f $(TARGET) *.o *.out *.log *.txt

.PHONY:run
run: $(TARGET)
	./$(TARGET) -v

.PHONY:valgrind
valgrind:	$(TARGET)
	valgrind ./$(TARGET)

.PHONY:gdb
gdb:  $(TARGET)
	gdb -q ./$(TARGET)

.PHONY:drd
drd:  $(TARGET)
	valgrind --tool=drd --log-file=drd.log ./$(TARGET)

.PHONY:helgrind
helgrind:  $(TARGET)
	valgrind --tool=helgrind --log-file=helgrind.log ./$(TARGET)
