CC       = gcc

compile:
	$(CC) base64.c logger.c -o base64
	./base64 --encode sgt-pepper.txt

clean:
	rm logger.o
	rm base.o
	rm base64.o
	rm encoded.txt
	rm decoded.txt