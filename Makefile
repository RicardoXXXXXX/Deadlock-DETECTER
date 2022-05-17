detect: detect.o process_data.o process_deadlock.o
	gcc -Wall -o detect detect.o process_data.o process_deadlock.o

detect.o: detect.c process_data.h process_deadlock.h
	gcc -Wall -c detect.c -o detect.o

process_data.o: process_data.c process_data.h
	gcc -Wall -c process_data.c -o process_data.o

process_deadlock.o: process_deadlock.c process_deadlock.h
	gcc -Wall -c process_deadlock.c -o process_deadlock.o

clean:
	rm -f *.o detect
	
