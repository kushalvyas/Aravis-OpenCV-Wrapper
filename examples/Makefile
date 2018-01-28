# sample make file.

CC=g++
MAIN_C = main.cpp
ADDN=Camera.cpp

INCLUDES= -I<PATH TO ARAVIS SRC>aravis/src/ -I/usr/include/glib-2.0/ -I/usr/lib/x86_64-linux-gnu/glib-2.0/include 

LINKAGES=-L/usr/lib -L/usr/local/lib -L/usr/lib/x86_64-linux-gnu/ -L<PATH TO ARARVIS SRC>/aravis/src/.libs/ 	-laravis-0.6 -lglib-2.0 -lm -pthread -lgio-2.0 -lgobject-2.0 -lxml2 -lgthread-2.0 -lglib-2.0 -lz -lusb-1.0  -lpng 

PKGS=`pkg-config --cflags --libs opencv` 

all:
	$(CC) -o main $(MAIN_C) $(ADDN) $(INCLUDES) $(LINKAGES) $(PKGS)
