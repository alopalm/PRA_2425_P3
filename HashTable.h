#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/alopalm/PRG_AV/pr1/PRA_2425_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	int alpha = n/max;
	ListLinked<TableEntry<V>>* table;
	int h(std::string key){
		int sum = 0;
		for (char c : key){
			sum += static_cast<int>(c);
		}
    		return sum % max;
		}


    public:
        
	HashTable(int size):n(0),max(size){
		table = new ListLinked<TableEntry<V>>[size]();
	}
	~HashTable(){
		delete[] table;
	}
	int capacity(){
	 return max;
	
	}
	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
    out << "HashTable [ entries: " << th.n 
        << ", capacity: " << th.max << " ]" << std::endl
        << "==================================" << std::endl;

    for (int i = 0; i < th.max; i++) {
        out << "===== Cubeta " << i << " ====" << std::endl;
            out << th.table[i] << std::endl; 
        }
    out << "===========" << std::endl;
    return out;
}

	V operator[](std::string key){
		return search(key);	
        }
	
	
	void insert(std::string key, V value) override{
		TableEntry<V> e(key,value);
                int b1 = h(key);
    		if (!table[b1].empty()) {
        		for (int i = 0; i < table[b1].size(); i++) {
            		if (table[b1].get(i).key == key) {
                		throw std::runtime_error("Clave ya existe en el diccionario");
            		}
        		}
    		}
    		table[b1].append(e);
    		n++;
	}		       

	V search(std::string key) override{
		
		TableEntry<V> e(key);
                int b1 = h(key);
		int pos = table[b1].search(e);
		if (pos == -1) {
			 throw std::runtime_error("No se encontró el elemento");
		
		}
		TableEntry<V> elem = table[b1].get(pos);
		return elem.value;
	
	}
	V remove(std::string key) override{
	
		TableEntry<V> e(key);
                int b1 = h(key);
                int pos = table[b1].search(e);
                if (pos == -1) {
                         throw std::runtime_error("No se encontró el elemento");

                }
                TableEntry<V> elem_remove = table[b1].remove(pos);
		n--;
   		return elem_remove.value;
		

	}
	int entries() override{
		return this-> n;
	
	}
        
};

#endif
