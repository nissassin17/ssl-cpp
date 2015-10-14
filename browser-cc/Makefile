
#all: $(OBJS)

CC = clang++
CFLAGS = -stdlib=libstdc++
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

all: $(OBJS)

test: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o browser

clean:
	rm -f *~ *.o browser
