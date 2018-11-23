g++ `pkg-config gtkmm-3.0 --cflags --libs` -c main.cpp elementproperty.cpp elementschema.cpp formulaparser.cpp molecularformula.cpp periodictablewindow.cpp
g++ main.o elementproperty.o elementschema.o formulaparser.o molecularformula.o periodictablewindow.o -o GTKPeriodicTable `pkg-config gtkmm-3.0 --cflags --libs`
./GTKPeriodicTable
