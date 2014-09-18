CC = g++
CFLAGS = -Wall -Werror -pedantic -Wno-long-long -O0 -ggdb 
compile: main.o exceptions.o tcp_layer.o http_layer.o client.o parsing.o
	 $(CC) $(CFLAGS) -o ./net_ninny $^ -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.cpp constants.h
exceptions.o: exceptions.cpp exceptions.h
tcp_layer.o: tcp_layer.cpp tcp_layer.h
http_layer.o: http_layer.cpp http_layer.h
client.o: client.cpp client.h
parsing.o: parsing.cpp parsing.h

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf net_ninny
