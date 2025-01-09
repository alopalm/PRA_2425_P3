#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        //miembros privados
	int nelem;//num elem almacenados
	BSNode<T> *root;//nodo raiz
	BSNode<T>* search(BSNode<T>* n, T e) const{//busqueda
		if (n == nullptr){
			throw std::runtime_error("No ha encontrado el elmento");
		}//si no encuentra el n en el sub-arbol que su raiz es n
		else if (n->elem < e) {//
         		   return search(n->right, e);//si el elem actual es menor que e (el que buscamos miramos en el sub arbol derecho MAYORES;
       		} else if (n->elem > e) {//si el elem es mayor al elemento a buscar
            		return search(n->left, e);//busca recursivamente pero en el subarbol de la izquierda 
        	} else {
            		return n;  // Nodo encontrado
        	}
	}
	BSNode<T>* insert(BSNode<T>* n, T e){//INSERCION
	
		if (n == nullptr) {
            return new BSNode<T>(e);

        } else if (n->elem == e) {
            throw std::runtime_error("Elemento duplicado");

        } else if (n->elem < e) {
            n->right = insert(n->right, e);  
        } else {
            n->left = insert(n->left, e);
        }

        return n;  // Devolver el nodo raíz del subárbol modificado
    }
	
	void print_inorder(std::ostream &out, BSNode<T>* n) const{//muestra a traves de out recorrido inorden
	
		if (n != nullptr) {
            		inorden(out,n->left);         // Recorrer subárbol izquierdo
                  	out << n->elem << " ";                // Procesar el nodo actual
            		inorden(out,n->right);       // Recorrer subárbol derecho
        }
	}
	  BSNode<T>* remove(BSNode<T>* n, T e) {//eliminar            
		if (n == nullptr){
			throw std::runtime_error("Elemento no encontrado");
		} 
		else if (e< n->elem){
			n->left = remove(n->left, e);
		} 
		else if (e >n->elem){
			n->right = remove(n->right, e);
		} 
		else{  // Nodo encontrado
            if (n->left!= nullptr && n->right!= nullptr) {
  		    n->elem = max(n->left);// Reemplazar con el máximo del subárbol izquierdo
                n->left = remove_max(n->left);// Eliminar el máximo del subárbol izquierdo
            } else {  // Uno o ningún hijo
                BSNode<T>* temp = n;
                n = (n->left != nullptr) ? n->left : n->right;
                delete temp;  // Liberar el nodo actual
            }
        }
        return n;
    }
	T max(BSNode<T>* n) const {
        if (n == nullptr) {
            throw std::runtime_error("Árbol vacío, no hay máximo");
        } else if (n->right != nullptr) {
            return max(n->right);  // Buscar en el subárbol derecho
        } else {
            return n->elem;  // El nodo más a la derecha es el máximo
        }
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            return n->left;  // Eliminar el nodo actual y retornar el izquierdo
        } else {
            n->right = remove_max(n->right);  // Continuar por el subárbol derecho
            return n;
        }
    }
	void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }
    public:
        
	BSTree():nelem(0),root(nullptr){}
	int size() const{
		return nelem;
	}
	T search(T e) const{// función lanzadera
	
		return search(root,e)->elem;
	
	}
	T operator[](T e) const{
	
		return search(e);
	
	}//BUSQUEDA;
	

	void insert(T e){//inserción
		insert(root,e)->elem;
	}
	
	friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){//recorrido e impresión del árbol

	  bst.print_inorder(out, bst.root);
	  return out;				               		}
	  void remove(T e){
	  	remove(root, e);
	  }
          
	  ~BSTree(){
	      delete_cascade(root);
	  }
};

#endif
