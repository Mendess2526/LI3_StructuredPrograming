package main.java.engine.calendario;

import main.java.engine.collections.FixedSizeList;

import java.util.function.Predicate;

class Day<T extends Chronological> {
    private final FixedSizeList<Hour<T>> hours;

    Day(){
        this.hours = new FixedSizeList<>(24);
    }

    void addElem(T c){
        int hour = c.getDate().getHour();
        if(this.hours.get(hour) == null) this.hours.set(hour, new Hour<>());
        this.hours.get(hour).addElem(c);
    }

    boolean iterateForward(Predicate<T> predicate){
        boolean r = true;
        for(int i = 0; r && i < 24; i++){
            Hour<T> h = this.hours.get(i);
            if(h != null) r = h.iterateForward(predicate);
        }
        return r;
    }

    boolean iterateBackwards(Predicate<T> predicate){
        boolean r = true;
        for(int i = 23; r && i >= 0 ; i--){
            Hour<T> h = this.hours.get(i);
            if(h != null) r = h.iterateBackwards(predicate);
        }
        return r;
    }

    long countElements(){
        long count = 0;
        for(int i = 0; i < 24; i++){
            Hour<T> h = this.hours.get(i);
            if(h != null) count += h.getCount();
        }
        return count;
    }
}
