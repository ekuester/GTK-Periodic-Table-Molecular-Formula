## Makefile
PROGRAM = GTKPeriodicTable
CXX= g++
CXXSOURCES=\
	main.cpp elementproperty.cpp elementschema.cpp formulaparser.cpp molecularformula.cpp\
	periodictablewindow.cpp printformoperation.cpp
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
OPTIONFLAGS= -g -O
PACKAGES= gtkmm-3.0
PKGCONFIG= pkg-config
CXXFLAGS= -std=c++11 -Wall $(OPTIONFLAGS)
CPPFLAGS:=  $(shell $(PKGCONFIG) --cflags $(PACKAGES))
LDFLAGS:= $(shell $(PKGCONFIG) --libs $(PACKAGES)) -ldl
.PHONY: all clean

all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) $(CXXOBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -frv $(CXXOBJECTS) $(PROGRAM)

run:
	./$(PROGRAM)
## eof Makefile

