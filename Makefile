mantribrot: mantribrot.c
	gcc mantribrot.c -o mantribrot -lm -Ofast
gif: mantribrot
	./mantribrot
	convert mantribrot_*.pgm -delay 4 mantribrot.gif
