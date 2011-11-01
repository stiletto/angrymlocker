
all: libangrymlocker.so

libangrymlocker.so: angrymlocker.c
	gcc -Wall -W -g -shared -fPIC -Wl,-export-dynamic -o libangrymlocker.so angrymlocker.c

install: libangrymlocker.so
	install -m 0755 -o root -g root libangrymlocker.so `pkg-config --variable=moduledir xorg-server`/

clean:
	rm -f libangrymlocker.so *.o

