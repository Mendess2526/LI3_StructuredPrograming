package engine.calendario;


import engine.collections.SortedLinkedList;

import java.util.Comparator;
import java.util.Iterator;
import java.util.function.Predicate;

/**
 * Classe que define uma hora.
 * @param <T> Tipo dos elemnetos guardados.
 */
class Hour<T extends Chronological> {
    /** Lista dos elementos da hora. */
    private final SortedLinkedList<T> elems;

    /**
     * Cria um hora.
     */
    Hour(){
        this.elems = new SortedLinkedList<>(Comparator.comparing(Chronological::getDate));
    }

    /**
     * Adiciona um elemento a uma hora.
     * @param c Elemento a adicionar.
     */
    void addElem(T c){
        this.elems.addLast(c);
    }

    /**
     * Itera sobre os elementos de uma hora por ordem cronológica.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateForward(Predicate<T> predicate){
        for(T elem : this.elems) if(!predicate.test(elem)) return false;
        return true;
    }

    /**
     * Itera sobre os elementos de uma hora por ordem cronológica inversa.
     * @param predicate Função a aplicar a todos os elementos.
     * @return {@code true} se a iteração deve continuar, {@code false} caso contrário.
     */
    boolean iterateBackwards(Predicate<T> predicate){
        boolean r = true;
        Iterator<T> it = this.elems.descendingIterator();
        while(r && it.hasNext()) r = predicate.test(it.next());
        return r;
    }

    /**
     * Conta o número de elementos que a hora tem.
     * @return O número de elementos que a hora tem.
     */
    int getCount(){
        return this.elems.size();
    }
}
