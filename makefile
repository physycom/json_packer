
EXE1=json_packer.exe
EXE2=json_packer2.exe

all: dirtree
	$(CXX) -std=c++11 -Isrc/jsoncons/src -o bin/$(EXE1) src/json_packer.cpp 
	$(CXX) -std=c++11 -Isrc/json/src -o bin/$(EXE2) src/json_packer2.cpp 

dirtree:
	mkdir -p bin

clean:
	rm -f bin/$(EXE1) bin/$(EXE2)

cleanall:
	rm -rf bin obj
