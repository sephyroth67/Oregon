CXXFLAGS += -O2 -Wall -g -pthread

all: test oregon

test: RCSwitch.o RcOok.o Sensor.o test.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

oregon: RCSwitch.o RcOok.o Sensor.o oregon.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi


clean:
	$(RM) *.o test oregon
