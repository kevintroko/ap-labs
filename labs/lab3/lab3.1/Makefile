CC       = gcc

compile:
	$(CC) -c logger.c -o logger.o
	$(CC) -c monitor.c -o monitor.o
	$(CC) logger.o monitor.o -o main.o
	./main.o .

clean: 
	rm logger.o
	rm monitor.o
	rm main.o
