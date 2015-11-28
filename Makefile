
#all: $(OBJS)

CC = g++
#CFLAGS = -stdlib=libstdc++
CFLAGS =
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o browser
	rm *.o
