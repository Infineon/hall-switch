FLAGS=

all: clean compile

compile:
	mkdir -p ../../../build
	g++ -c $(FLAGS) -o ../../../build/hall-speed ../../corelib/hall-speed.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch ../../corelib/hall-switch.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-int ../../corelib/hall-switch-int.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-pal-rpi pal/hall-pal-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-platf-rpi wrapper/hall-platf-rpi.cpp
	g++ -c $(FLAGS) -o ../../../build/hall-switch-rpi wrapper/hall-switch-rpi.cpp -I../../corelib/
	g++ -c $(FLAGS) -o ../../../build/test ../../test.cpp

clean:
	rm -f ../../../build/*
