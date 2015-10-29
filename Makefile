########################################
# Makefile 
#
#	Author: Jeff Wen
# Email: mjeffwhen@gmail.com
########################################

OBJS = hill-algorithm.o main.o
CC = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c
LFLAGS = -Wall

ed: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ed

$(OBJS): hill-algorithm.h

hill-algorithm.o: hill-algorithm.cxx
	$(CC) $(CFLAGS) hill-algorithm.cxx

main.o: main.cxx
	$(CC) $(CFLAGS) main.cxx

clean: 
	rm *.o ed

