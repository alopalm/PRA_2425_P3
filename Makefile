bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

bin/testHashTable: testHashTable.cpp HashTable.h
	mkdir -p bin
	g++ -o bin/testHashTable testHashTable.cpp Dict.h HashTable.h TableEntry.h 

bin/testBSTree: testBSTree.cpp BSTree.h
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp BSNode.h BSTree.h

bin/testBSTreeDict: testBSTreeDict.cpp BSTreeDict.h
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp Dict.h BSTreeDict.h BSNode.h TableEntry.h
clean:
	rm -rf *.o *.gch bin
