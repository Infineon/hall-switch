CPPFLAGS = -DHALL_SWITCH_FRAMEWORK=HALL_SWITCH_FRMWK_RPI

all: examples/hall-polling examples/hall-interrupt

lib:
	mkdir -p ../../../build
	g++ -c $(CPPFLAGS) -o ../../../build/hall-speed.o ../../corelib/hall-speed.cpp
	g++ -c $(CPPFLAGS) -o ../../../build/hall-switch.o ../../corelib/hall-switch.cpp
	g++ -c $(CPPFLAGS) -o ../../../build/hall-switch-int.o ../../corelib/hall-switch-int.cpp
	g++ -c $(CPPFLAGS) -o ../../../build/hall-pal-rpi.o pal/hall-pal-rpi.cpp
	g++ -c $(CPPFLAGS) -o ../../../build/hall-platf-rpi.o wrapper/hall-platf-rpi.cpp
	g++ -c $(CPPFLAGS) -o ../../../build/hall-switch-rpi.o wrapper/hall-switch-rpi.cpp -I../../corelib
	
examples/hall-polling-c:
	g++ -c $(CPPFLAGS) -o ../../../build/hall-polling.o examples/hall-polling.cpp -Iwrapper/ -I../../corelib
examples/hall-polling-l:
	g++ $(CPPFLAGS) -o ../../../build/hall-polling ../../../build/*.o -I/usr/local/include -L/usr/local/lib -lwiringPi
	
examples/hall-interrupt-c:
	g++ -c $(CPPFLAGS) -o ../../../build/hall-interrupt.o examples/hall-interrupt.cpp -Iwrapper/ -I../../corelib
examples/hall-interrupt-l:
	g++ $(CPPFLAGS) -o ../../../build/hall-interrupt ../../../build/*.o -I/usr/local/include -L/usr/local/lib -lwiringPi

examples/hall-polling: lib examples/hall-polling-c examples/hall-polling-l
examples/hall-interrupt: lib examples/hall-interrupt-c examples/hall-interrupt-l

ci: lib examples/hall-polling-c examples/hall-interrupt-c

clean:
	rm -f ../../../build/*
