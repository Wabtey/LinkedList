#
# Link
#

CFLAGS = -Wall -g

bin/test_list: obj/list.o obj/test_list.o

	gcc $(CFLAGS) -o test_list obj/list.o obj/test_list.o
#


#
# Objets of TP Lists
#

obj/list.o: src/list.c include/list.h

#on s'assure que le dossier obj exsite 
	mkdir -p obj    			
#on compile 
	gcc $(CFLAGS) -c src/list.c -I./include -o obj/list.o


obj/test_list.o: src/test_list.c include/list.h

	gcc $(CFLAGS) -c src/test_list.c -I./include -o obj/test_list.o 
# 

#
# Listing creation in pdf
#

listing:
	a2ps -o listing.ps include/list.h src/list.c src/test_list.c
	ps2pdf listing.ps
	rm listing.ps

#
# Remove files
#

clean :
	rm obj/*.o test_list  





#
# Test the functionality 
#

test :
# To be completed
