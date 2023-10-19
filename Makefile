CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

binclock-gtk : 
	cc -o dlogout dlogout.c $(CFLAGS) $(LIBS)

install :
	cp dlogout /usr/local/bin/

uninstall :
	rm /usr/local/bin/dlogout

clean :
	rm dlogout
