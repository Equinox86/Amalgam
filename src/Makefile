all: amalgam clean

%.o: %.cpp
	g++ $< -I/usr/include -c -o $@ 

amalgam: security.o amalgam.o fileman.o network.o MurmurHash2.o
	g++ $^ -o $@ -L/usr/lib/x86_64-linux-gnu -lssl -lcrypto -lpthread

clean: 
	-rm -rf *.o