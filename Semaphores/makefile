CFLAGS=-Wall -Wextra -std=c11 -O2 -lpthread

main: main.o fifo.o
	gcc -o main main.o fifo.o $(CFLAGS)
	
fifo.o: fifo.c fifo.h
	gcc -c fifo.c $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

clean:
	@echo "Removing unnecessary files..."
	rm fifo.o
	rm main.o
	rm main
	@echo "Done."