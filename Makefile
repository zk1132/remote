CC := clang

.PHONY: all
all: receive send

receive: receive.o register.o
	$(CC) -o $@ $^

send: send.o register.o
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm *.o send receive -rf
