package stackoverflow;

import java.util.Comparator;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Collection;

public class SortedLinkedList<T> extends LinkedList<T>{

    /**
     * Appends the specified element to the end of this list.
     *
     * <p>This method is equivalent to {@link #add}.
     * @param o the element to add
     * @param c the comparator to insert sorted
     */
    public void addLast(T o, Comparator<T> c){
        if(this.size() == 0){
            super.addFirst(o);
            return;
        }
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

    public void addLast(T o, Comparator<T> c, int max){
        if(this.size() == 0){
            this.add(o);
            return;
        }
        ListIterator<T> it = this.listIterator(this.size() - 1);
        it.next();
        while(max > 0 && it.hasPrevious()){
            T t = it.previous();
            if(c.compare(o,t) < 0){
                it.next();
                it.add(o);
                max = 0;
            }else{
                max--;
            }
        }
        if(max > 0) it.add(o);
    }

    public void addFirst(T o, Comparator<T> c){
        if(this.size() == 0){
            super.add(o);
            return;
        }
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

    public void addFirst(T o, Comparator<T> c, int max){
        if(this.size() == 0){
            super.add(o);
            return;
        }
        ListIterator<T> it = this.listIterator();
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
}
