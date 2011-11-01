
all: libangrymlocker.so

libangrymlocker.so: angrymlocker.c
#	gcc -shared -Wl,-soname,angrymlocker -fPIC -o libangrymlocker.so angrymlocker.c
	gcc -Wall -W -g -shared -fPIC -Wl,-export-dynamic -o libangrymlocker.so angrymlocker.c

clean:
	rm -f libangrymlocker.so *.o

