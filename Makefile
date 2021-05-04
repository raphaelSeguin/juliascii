INCLUDES = -I./include

.DEFAULT: make mbrot

mbrot: mbrot.c
	gcc -o mbrot mbrot.c $(INCLUDES)
julia: julia.c
	gcc -o julia julia.c $(INCLUDES) -lm
