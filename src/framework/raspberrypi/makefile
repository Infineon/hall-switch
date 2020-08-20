FLAGS=

all: clean example/hall-polling

lib:
	mkdir -p ../../../build
	g++ -c $(FLAGS) -o ../../../build/hall-speed.o ../../corelib/hall-speed.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch.o ../../corelib/hall-switch.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-int.o ../../corelib/hall-switch-int.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-pal-rpi.o pal/hall-pal-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-platf-rpi.o wrapper/hall-platf-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-rpi.o wrapper/hall-switch-rpi.cpp -I../../corelib
	
examples/hall-polling: lib
	g++ -c $(FLAGS) -o ../../../build/hall-polling.o examples/hall-polling.cpp -Iwrapper/ -I../../corelib
	g++ $(FLAGS) -o ../../../build/hall-polling ../../../build/*.o -I/usr/local/include -L/usr/local/lib -lwiringPi
	
examples/hall-interrupt: lib
	g++ -c $(FLAGS) -o ../../../build/hall-interrupt.o examples/hall-interrupt.cpp -Iwrapper/ -I../../corelib
	g++ $(FLAGS) -o ../../../build/hall-interrupt ../../../build/*.o -I/usr/local/include -L/usr/local/lib -lwiringPi

clean:
	rm -f ../../../build/*
