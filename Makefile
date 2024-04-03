CC = g++
FLAGS = -Werror -std=c++11

OBJS = main.o util.o database.o
TARGET = main.exe

$(TARGET): $(OBJS)
	${CC} -o $@ $(OBJS)

.c.o :
	$(CC) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY : clean
