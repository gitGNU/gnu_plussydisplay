
ANIM ?= anim_test
CFLAGS = -fPIC -std=c99 -DANIMATION=$(ANIM)

all:
	gcc $(CFLAGS) -c ../uc/src/animations/common.c -o common.o
	gcc $(CFLAGS) -c ../uc/src/animations/$(ANIM).c -o $(ANIM).o
	gcc $(CFLAGS) -c sim.c -o sim.o
	gcc -shared -fPIC sim.o common.o $(ANIM).o -o sim.so -lpython2.7
	./test.py

clean:
	-rm *.o *.so

.PHONY: all clean

