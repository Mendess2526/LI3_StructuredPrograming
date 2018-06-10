package stackoverflow;

import java.util.Collection;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.ListIterator;

public class SortedLinkedList<T> extends LinkedList<T>{

    private int maxSize;
    private Comparator<T> c;

    public SortedLinkedList(Comparator<T> c){
        super();
        this.c = c;
        this.maxSize = -1;
    }

    public SortedLinkedList(Comparator<T> c, int maxSize){
        super();
        this.c = c;
        this.maxSize = maxSize;
    }

    @Override
    public boolean add(T t){
        if(this.size() == 0)
            return super.add(t);
        if(this.c.compare(super.peekLast(), t) < 0){
            if(this.size() < this.maxSize || this.maxSize != - 1)
                super.addLast(t);
        }else{
            this.addFirst(t);
        }

        return true;
    }

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
            if(c.compare(o,t) > 0){
                it.next();
                it.add(o);
                inserted = true;
            }
        }
        if(!inserted) it.add(o);
    }

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

    public void trim(){
        ListIterator<T> t = this.listIterator(this.size());
        while(this.size() > this.maxSize){
            t.previous();
            t.remove();
        }
    }

    @Override
    public boolean addAll(Collection<? extends T> c){
        for(T t: c) this.add(t);
        return true;
    }
}
