FLAGS=

all: clean compile

compile:
	mkdir -p ../../../build
	g++ -c $(FLAGS) -o ../../../build/hall-speed.o ../../corelib/hall-speed.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch.o ../../corelib/hall-switch.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-int.o ../../corelib/hall-switch-int.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-pal-rpi.o pal/hall-pal-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-platf-rpi.o wrapper/hall-platf-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-rpi.o wrapper/hall-switch-rpi.cpp -I../../corelib
	g++ -c $(FLAGS) -o ../../../build/hall_switch.o hall_switch.cpp -Iwrapper/ -I../../corelib
	g++ $(FLAGS) -o ../../../build/hall_switch ../../../build/*.o -I/usr/local/include -L/usr/local/lib -lwiringPi

clean:
	rm -f ../../../build/*
