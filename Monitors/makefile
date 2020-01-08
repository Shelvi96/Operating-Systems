CFLAGS=-Wall -Wextra -Wshadow -std=c++11 -lpthread

main: main.o mymonitor.o 
	g++ -o main main.o mymonitor.o $(CFLAGS)
	
mymonitor.o: mymonitor.cpp mymonitor.h monitor.h 
	g++ -c mymonitor.cpp $(CFLAGS)

main.o: main.cpp mymonitor.h
	g++ -c main.cpp $(CFLAGS)

clean:
	@echo "Removing unnecessary files..."
	rm mymonitor.o
	rm main.o
	rm main
	@echo "Done."