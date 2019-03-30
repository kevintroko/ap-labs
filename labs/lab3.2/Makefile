CC       = gcc

compile:
	$(CC) base64.c logger.c -o base64

encode:
	./base64 --encode sgt-pepper.txt

decode: 
	./base64 --decode encoded.txt

text:
	wget http://textfiles.com/stories/vgilante.txt
	wget http://textfiles.com/stories/sick-kid.txt
	wget http://textfiles.com/stories/aesop11.txt

clean:
	rm logger.o
	rm base.o
	rm base64.o
	rm encoded.txt
	rm decoded.txt
	rm vgilante.txt
	rm sick-kid.txt
	rm aesop11.txt