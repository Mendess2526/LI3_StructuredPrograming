package stackoverflow.calendario;

import stackoverflow.collections.SortedLinkedList;

import java.util.Comparator;
import java.util.Iterator;

class Hour<T extends Chronological> {
    private int count;
    private SortedLinkedList<T> elems;

    Hour(){
        this.count = 0;
        this.elems = new SortedLinkedList<>(Comparator.comparing(Chronological::getDate));
    }

    void addElem(T c){
        this.elems.addLast(c);
        this.count++;
    }

    boolean iterateForward(CalendarioPredicate<T> predicate){
        for(T elem : this.elems) if(!predicate.test(elem)) return false;
        return true;
    }

    boolean iterateBackwards(CalendarioPredicate<T> predicate){
        boolean r = true;
        Iterator<T> it = this.elems.descendingIterator();
        while(r && it.hasNext()) r = predicate.test(it.next());
        return r;
    }

    int getCount(){
        return this.count;
    }
}
