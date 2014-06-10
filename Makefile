MAKE = make
CC = g++
CFLAGS = -std=c++11 -Wc++11-extensions -lfltk -lrtaudio

all: gilbertcore
	$(CC) $(CFLAGS) main.cpp -o gilbertDevelopmentFltk

gilbertcore:
	$(MAKE) -C gilbertcore

clean:
	rm *.o
	rm gilbertDevelopmentFltk