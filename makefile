
EXE1=json_packer.exe
#EXE2=json_packer2.exe

all: dirtree
	$(CXX) -std=c++11 -Isrc -o bin/$(EXE1) src/json_packer.cpp 
#	$(CXX) -std=c++11 -Isrc -o bin/$(EXE2) src/json_packer2.cpp 

dirtree:
	mkdir -p bin

