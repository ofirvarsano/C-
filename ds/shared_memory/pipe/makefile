#makefile Graph

TARGET= pipe.out
CC= g++
CPPFLAGS= -cpp -g
OBJS= pipe.o

all: $(TARGET)

run:$(TARGET)
	./$(TARGET)

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
