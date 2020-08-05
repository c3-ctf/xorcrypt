xorcrypt: main.c
	$(CC) main.c -o xorcrypt
install: xorcrypt
	cp xorcrypt /usr/bin/xorcrypt
	chown ${UID}:${UID} /usr/bin/xorcrypt
clean:
	rm xorcrypt
