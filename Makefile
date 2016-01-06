########################################
# Makefile 
#
#	Author: Jeff Wen
# Email: mjeffwhen@gmail.com
########################################

OBJS = hill-algorithm.o main.o
CC = 
CXX = g++
DEBUG = -g
CFLAGS = -std=c++11 -Wall -c
LFLAGS = -Wall

ed: $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o ed

$(OBJS): hill-algorithm.h

hill-algorithm.o: hill-algorithm.cxx
	$(CXX) $(CFLAGS) hill-algorithm.cxx

main.o: main.cxx
	$(CXX) $(CFLAGS) main.cxx

clean: 
	rm *.o ed

