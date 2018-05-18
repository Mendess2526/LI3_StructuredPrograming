package stackoverflow;

import java.util.Comparator;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Collection;

public class SortedLinkedList<T> extends LinkedList<T>{

    /**
     * Inserts the specified element at the beginning of this list.
     * @param t the element to add
     */
    @Override
    public void addFirst(T t){
        throw new UnsupportedOperationException();
    }

    /**
     * Appends the specified element to the end of this list.
     *
     * <p>This method is equivalent to {@link #add}.
     * @param t the element to add
     */
    @Override
    public void addLast(T t){
        throw new UnsupportedOperationException();
    }

    /**
     * Appends the specified element to the end of this list.
     *
     * <p>This method is equivalent to {@link #add}.
     * @param o the element to add
     * @param c the comparator to insert sorted
     */
    public void addLast(T o, Comparator<T> c){
        if(this.size() == 0) this.add(o);
        boolean inserted = false;
        ListIterator<T> it = this.listIterator(this.size() - 1);
        it.next();
        while(!inserted && it.hasPrevious()){
            T t = it.previous();
            if(c.compare(o,t) < 0){
                it.next();
                it.add(o);
                inserted = true;
            }
        }
        if(!inserted) it.add(o);
    }

    /**
     * Appends the specified element to the end of this list.
     *
     * <p>This method is equivalent to {@link #addLast}.
     * @param t element to be appended to this list
     * @return {@code true} (as specified by {@link Collection#add})
     */
    @Override
    public boolean add(T t) throws UnsupportedOperationException{
        throw new UnsupportedOperationException();
    }

    /**
     * Inserts the specified element at the specified position in this list.
     * Shifts the element currently at that position (if any) and any
     * subsequent elements to the right (adds one to their indices).
     * @param index   index at which the specified element is to be inserted
     * @param element element to be inserted
     * @throws UnsupportedOperationException This operation is not supported
     */
    @Override
    public void add(int index, T element) throws UnsupportedOperationException{
        throw new UnsupportedOperationException();
    }

    public void add(T o, Comparator<T> c){
        if(this.size() == 0) super.add(o);
        boolean inserted = false;
        ListIterator<T> it = this.listIterator();
        while(!inserted && it.hasNext()){
            T t = it.next();
            if(c.compare(o,t) < 0){
                it.previous();
                it.add(o);
                inserted = true;
            }
        }
        if(!inserted) it.add(o);
    }

    public void add(T o, Comparator<T> c, int max){
        add(o,c);
    }
}
