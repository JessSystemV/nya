nya: nya.c
	cc nya.c -std=c17 -O3 -o nya
clean:
	rm -f nya
install:
	cp nya /usr/local/bin/nya
