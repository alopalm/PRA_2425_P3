#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
	BSTree<TableEntry<V>>* tree;
    public:
        BSTreeDict(){
		tree = new BSTree<TableEntry<V>>();	
	}
	~BSTreeDict(){
		delete tree;
	}
	V operator[](std::string key) const {
        	TableEntry<V> entry(key);
                return tree->search(entry).value;
	}

  
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry); 
    }
 
    V search(std::string key) override{
        TableEntry<V> entry(key, V());
        return tree->search(entry).value;
    }
V remove(std::string key) override {
    TableEntry<V> entry(key, V());  // Crear un TableEntry con la clave y un valor por defecto
    TableEntry<V> found = tree->search(entry);  // Buscar el TableEntry en el árbol
    tree->remove(entry);  // Eliminar el TableEntry del árbol
    return found.value;  // Devolver el valor asociado al TableEntry eliminado
}


    int entries() override {
        return tree->size();
    }

    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &dict) {
        out << *(dict.tree);
        return out;
    }
        
};

#endif
