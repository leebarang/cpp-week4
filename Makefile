CC = g++
FLAGS = -Werror -std=c++11

OBJS = main.o util.o database.o
TARGET = main.exe

$(TARGET): $(OBJS)
	${CC} -o $@ $(OBJS)

main.o: main.cpp database.h
    ${CC} ${FLAGS} -c $<

util.o: util.cpp database.h
    ${CC} ${FLAGS} -c $<

database.o: database.cpp database.h
    ${CC} ${FLAGS} -c $<

clean:
	rm -f $(OBJS) $(TARGET)
