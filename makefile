
EXE1=packer_jsoncons.exe
EXE2=packer_nlohmannjson.exe

all: dirtree
	$(CXX) -std=c++11 -Isrc/jsoncons/src -o bin/$(EXE1) src/packer_jsoncons.cpp 
	$(CXX) -std=c++11 -Isrc/json/src -o bin/$(EXE2) src/packer_nlohmannjson.cpp 

dirtree:
	mkdir -p bin

clean:
	rm -f bin/$(EXE1) bin/$(EXE2)

cleanall:
	rm -rf bin obj
