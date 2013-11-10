OUT := pass
CC := clang

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

.PHONY: all
all: $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $(OUT) $^


.PHONY: clean
clean:
	rm *.o $(OUT) -rf
