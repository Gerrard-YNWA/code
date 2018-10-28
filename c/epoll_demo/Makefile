CFLAGS = -Wall -g -std=c99
CC = gcc
all : epoll_server epoll_client
.PHONY: all

epoll_server : epoll_server.c
	$(CC) $(CFLAGS) epoll_server.c -o $@
epoll_client : epoll_client.c
	$(CC) $(CFLAGS) epoll_client.c -o $@
clean :
	rm -f epoll_server epoll_client
