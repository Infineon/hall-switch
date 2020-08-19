FLAGS=

all: clean example/lib-polling

lib:
	mkdir -p ../../../build
	g++ -c $(FLAGS) -o ../../../build/hall-speed.o ../../corelib/hall-speed.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch.o ../../corelib/hall-switch.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-int.o ../../corelib/hall-switch-int.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-pal-rpi.o pal/hall-pal-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-platf-rpi.o wrapper/hall-platf-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-rpi.o wrapper/hall-switch-rpi.cpp -I../../corelib
	
example/lib-polling: lib
	g++ -c $(FLAGS) -o ../../../build/lib-polling.o examples/lib-polling.cpp -Iwrapper/ -I../../corelib
	g++ $(FLAGS) -o ../../../build/lib-polling ../../../build/*.o -I/usr/local/include -L/usr/local/lib -lwiringPi
	
example/lib-interrupt: lib
	g++ -c $(FLAGS) -o ../../../build/lib-interrupt.o examples/lib-interrupt.cpp -Iwrapper/ -I../../corelib
	g++ $(FLAGS) -o ../../../build/lib-interrupt ../../../build/*.o -I/usr/local/include -L/usr/local/lib -lwiringPi

clean:
	rm -f ../../../build/*
