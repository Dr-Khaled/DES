CC = g++
CFLAGS = -g -Wall -fdiagnostics-color=always
DEPS = sim.cpp item.cpp

sim: $(DEPS) 
	$(CC) $(DEPS) $(CFLAGS) -o $@

