# Makefile
# Written by  : Chvatal Martin & Peschke Lena
# Written for : LiU, TDTS06, lab 2
# Date        : Sept. 2014
# Version     : 1.0

CC = g++
CFLAGS = -Wall -Werror -pedantic -Wno-long-long -O0 -ggdb 
compile: client.o exceptions.o http_layer.o main.o parsing.o server.o tcp_layer.o
	 $(CC) $(CFLAGS) -o ./net_ninny $^ -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

client.o: client.cpp client.h
exceptions.o: exceptions.cpp exceptions.h
http_layer.o: http_layer.cpp http_layer.h
main.o: main.cpp constants.h
tcp_layer.o: tcp_layer.cpp tcp_layer.h
parsing.o: parsing.cpp parsing.h
server.o: server.cpp server.h

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf net_ninny
