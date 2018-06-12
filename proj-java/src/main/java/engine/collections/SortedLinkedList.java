package engine.collections;

import java.util.Collection;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.ListIterator;

/**
 * Lista ligada ordenada.
 * @param <T> Tipo dos elementos guardados.
 */
public class SortedLinkedList<T> extends LinkedList<T>{
    /** Tamanho máximo da lista. */
    private final int maxSize;
    /** Comparador dos elementos. */
    private final Comparator<T> c;

    /**
     * Cria uma lista ligada ordenada.
     * @param c Comparador para ordenar a lista.
     */
    public SortedLinkedList(Comparator<T> c){
        super();
        this.c = c;
        this.maxSize = -1;
    }

    /**
     * Cria uma lista ligada ordenada com tamanho máximo.
     * @param c Comparador para ordenar a lista
     * @param maxSize Tamanho máximo da lista.
     */
    public SortedLinkedList(Comparator<T> c, int maxSize){
        super();
        this.c = c;
        this.maxSize = maxSize;
    }


    /**
     * {@inheritDoc}
     */
    @Override
    public boolean add(T t){
        if(this.size() == 0)
            return super.add(t);
        if(this.c.compare(super.peekLast(), t) < 0){
            if(this.size() < this.maxSize || this.maxSize == - 1)
                super.addLast(t);
        }else{
            this.addFirst(t);
        }

        return true;
    }

    /**
     * Adiciona um elemento começando pelo fim da lista.
     * @param o Elemento a adicionar.
     */
    public void addLast(T o){
        if(this.maxSize != -1) throw new UnsupportedOperationException();
        if(this.size() == 0){
            super.add(o);
            return;
        }
        ListIterator<T> it = this.listIterator(this.size());
        boolean inserted = false;
        while(!inserted && it.hasPrevious()){
            T t = it.previous();
            if(this.c.compare(o,t) > 0){
                it.next();
                it.add(o);
                inserted = true;
            }
        }
        if(!inserted) it.add(o);
    }

    /**
     * Adiciona um elemento começando pelo início da lista.
     * @param o Elemento a adicionar.
     */
    public void addFirst(T o){
        if(this.size() == 0){
            super.add(o);
            return;
        }
        ListIterator<T> it = this.listIterator();
        int max = this.maxSize == -1 ? Integer.MAX_VALUE : this.maxSize;
        while(max > 0 && it.hasNext()){
            T t = it.next();
            if(c.compare(o,t) < 0){
                it.previous();
                it.add(o);
                max = 0;
            }else{
                max--;
            }
        }
        if(max > 0) it.add(o);
    }


    /**
     * {@inheritDoc}
     */
    @Override
    public boolean addAll(Collection<? extends T> c){
        for(T t: c) this.add(t);
        return true;
    }
}
