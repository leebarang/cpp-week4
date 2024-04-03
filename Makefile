FLAGS = -Werror -std=c++11

SRCS = main.cpp util.cpp database.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main.exe

TARGET = main.o util.o database.o database.h
	g++ -o main.exe main.o util.o database.o

main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

util.o: util.cpp
	g++ ${FLAGS} -c util.cpp

database.o: database.cpp
	g++ ${FLAGS} -c database.cpp

clean:
    rm -f $(OBJS) $(TARGET)