CC = g++
FLAGS = -Werror -std=c++11

OBJS = main.o util.o database.o
TARGET = main.exe

$(TARGET): $(OBJS)
	${CC} -o $@ $(OBJS)

%.o: %.cpp %.h
	${CC} ${FLAGS} -c $<

clean:
	rm -f $(OBJS) $(TARGET)
