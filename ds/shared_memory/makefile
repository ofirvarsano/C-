#makefile Graph

TARGET= $(shell basename $(CURDIR))_test.out
CC= g++
CPPFLAGS= -cpp -g
OBJS= pWrite.o

all: $(TARGET)

run:$(TARGET)
	./$(TARGET) 100

gdb:$(TARGET)
	gdb ./$(TARGET) -q

clean:$(TARGET)
	rm -f $(TARGET) depends $(OBJS) *.gch
	
valgrind:$(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

lib: $(LIB)	

SRCS=$(OBJS:.o=.cpp)
$(TARGET): depends $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(TARGET)
depends:
	$(CC) -MM -I./ $(SRCS) > depends
include depends	
