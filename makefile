TEST_NAME := test_suckd
NAME   	  := suckd

CC     	    := gcc
CFLAGS      := -std=c11 -Wall -Wextra -Wpedantic -O2
TEST_CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Og -ggdb -fsanitize=address -fno-omit-frame-pointer

LIBS    := -lcriterion
INCLUDE	:= -Iinclude/
SRCS    := src/*/*.c

TEST_EXCL := src/suckd/main.c
TEST_SRCS := $(wildcard src/*/*.c test/*.c)
TEST_SRCS := $(filter-out $(TEST_EXCL),$(TEST_SRCS))

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o bin/$(NAME)

tests:
	$(CC) $(TEST_CFLAGS) $(LIBS) $(INCLUDE) $(TEST_SRCS) -o bin/$(TEST_NAME)

clean:
	rm -f test_suckd
	rm -f suckd
