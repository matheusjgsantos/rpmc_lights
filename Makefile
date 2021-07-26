OBJS	= PiGpio.o Led.o
SOURCE	= testLeds.c
HEADER	= 
OUT	= testLeds
CC	 = gcc
FLAGS	 = -c -Wall
LFLAGS	 = -lwiringPi

all: $(OBJS)
	$(CC) $(SOURCE) -g $(OBJS) -o $(OUT) $(LFLAGS)

testLeds: testLeds.c
	$(CC) $(FLAGS) testLeds.c 


clean:
	rm -f $(OBJS) $(OUT)
