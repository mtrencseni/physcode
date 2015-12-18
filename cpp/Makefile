
CC=g++
IDIR=include
CFLAGS=-std=c++11 -I$(IDIR)
DEPS = $(IDIR)/Quantity.h $(IDIR)/Unit.h $(IDIR)/Vec.h $(IDIR)/VecQuantity.h

all: bin/CoulombNBody3D \
	 bin/DampedHarmonicOscillator \
	 bin/DampedHarmonicOscillator2D \
	 bin/GravityNBody3D \
	 bin/HarmonicOscillator \
	 bin/HarmonicOscillator2D \
	 bin/PistonGas

bin/%: %.cpp $(DEPS) | bin
	$(CC) -o $@ $(notdir $@).cpp $(CFLAGS)

bin:
	mkdir -p bin

clean:
	rm -rf bin
