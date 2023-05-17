  CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCE = main.c
TARGET = my_ls

$(TARGET):$(SOURCE)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)