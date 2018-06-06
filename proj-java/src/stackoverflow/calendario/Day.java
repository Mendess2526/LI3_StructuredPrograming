package stackoverflow.calendario;

class Day<T extends Chronological> {
    private FixedSizeList<Hour<T>> hours;

    Day(){
        this.hours = new FixedSizeList<>(24);
    }

    void addElem(T c){
        int hour = c.getDate().getHour();
        if(this.hours.get(hour) == null) this.hours.set(hour, new Hour<>());
        this.hours.get(hour).addElem(c);
    }

    boolean iterateForward(CalendarioPredicate<T> predicate){
        boolean r = true;
        for(int i = 0; r && i < 24; i++){
            if(this.hours.get(i) != null) r = this.hours.get(i).iterateForward(predicate);
        }
        return r;
    }

    boolean iterateBackwards(CalendarioPredicate<T> predicate){
        boolean r = true;
        for(int i = 23; r && i >= 0 ; i--){
            if(this.hours.get(i) != null) r = this.hours.get(i).iterateBackwards(predicate);
        }
        return r;
    }

    long countElements(){
        long count = 0;
        for(int i = 0; i < 24; i++)
            if(this.hours.get(i) != null)
                count += this.hours.get(i).getCount();
        return count;
    }
}
