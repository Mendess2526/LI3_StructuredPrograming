package stackoverflow.calendario;

import stackoverflow.SortedLinkedList;

import java.util.Comparator;
import java.util.Iterator;

class Hour {
    private int count;
    private SortedLinkedList<Chronological> elems;

    Hour(){
        this.count = 0;
        this.elems = new SortedLinkedList<>();
    }

    void addElem(Chronological c){
        this.elems.addLast(c , Comparator.comparing(Chronological::getDate));
    }

    boolean iterateForward(CalendarioPredicate<? extends Chronological> predicate){
        for(Chronological elem : this.elems) if(predicate.apply(elem)) return false;
        return true;
    }

    boolean iterateBackwards(CalendarioPredicate<? extends Chronological> predicate){
        boolean r = true;
        Iterator<Chronological> it = this.elems.descendingIterator();
        while(r && it.hasNext()) r = predicate.apply(it.next());
        return r;
    }

    int getCount(){
        return this.count;
    }
}
