CC=gcc
CFLAGS=-c -Wall -g

all: 340_project

p1: 340_project.o
	$(CC) 340_project.o p1.o -o p1
	
project.o: 340_project.c
	$(CC) $(CFLAGS) 340_project.c
	
run:
	./340_project
	
tarball: 
	tar -cvzf Gavin_Bryce.tar.gz Makefile 340_project.c README.TXT
