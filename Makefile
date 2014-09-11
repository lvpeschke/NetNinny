CC = g++
CFLAGS = -Wall -Werror -pedantic -Wno-long-long -O0 -ggdb 
compile: main.o exceptions.o tcp_layer.o
	 $(CC) $(CFLAGS) -o ./assignment_2 $^ -lpthread

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.cpp
exceptions.o: exceptions.cpp exceptions.h
tcp_layer.o: tcp_layer.cpp tcp_layer.h


clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
