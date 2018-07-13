
CC = gcc
CLFAGS = -Wall -Wextra -Werror
SOURCE = 
OBJECT = $(SOURCE:.c=.o)

ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif
NAME = libft_malloc_$(HOSTTYPE).so

ifeq ($(INSTALL_PATH),)
	INSTALL_PATH = .
endif
LINK = $(INSTALL_PATH)/libft_malloc.so
LIBFT = libft/libft.a

all: $(NAME)

install: $(TARGET)
	@ln -s $(TARGET) $(LINK)

$(NAME): $(OBJECT)
	@echo "\033[34mcreating $(NAME)\033[39m"
	@$(CC) -shared $(SOURCE) -fPIC -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make -C libft

clean:
	@make -C libft clean
	@echo "\033[34mremoving object files of $(NAME)\033[39m"
	@rm -f $(OBJECT)

fclean: clean
	@make -C libft fclean
	@echo "\033[34mremoving $(NAME)\033[39m"
	@rm -f $(NAME) $(LINK)

re: fclean all

