
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC -g -DDEBUG
LDFLAGS = -shared
SOURCE = libft_malloc.c       \
         zone_malloc.c        \
         zone_free.c          \
         zone_realloc.c       \
         zone_tiny_alloc.c    \
         zone_tiny_free.c     \
         zone_tiny_realloc.c  \
         zone_small_alloc.c   \
         zone_small_free.c    \
         zone_small_realloc.c \
         zone_large_alloc.c   \
         zone_large_free.c    \
         zone_large_realloc.c \
         show_alloc_mem.c     \
         utils.c
OBJECT = $(SOURCE:.c=.o)

ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif
NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

all: $(NAME)

$(NAME): $(OBJECT)
	@echo "\033[34mcreating $(NAME)\033[39m"
	@$(CC) $(CFLAGS) -shared $(SOURCE) -o $(NAME)
	@echo "\033[34m$(LINK) as a symlink to $(NAME)\033[39m"
	@rm -f $(LINK)
	@ln -s $(NAME) $(LINK)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

test: $(NAME) test.c
	$(CC) $(CFLAGS) -c test.c -o test.o
	$(CC) $(CFLAGS) test.o libft_malloc.so $(NAME) -o test
	rm -f test.o

clean:
	@echo "\033[34mremoving object files of $(NAME)\033[39m"
	@rm -f $(OBJECT)

fclean: clean
	@echo "\033[34mremoving $(NAME)\033[39m"
	@rm -f $(NAME) $(LINK) test

re: fclean all

