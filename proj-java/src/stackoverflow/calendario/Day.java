package stackoverflow.calendario;

class Day {
    private Hour[] hours;

    Day(){
        this.hours = new Hour[24];
    }

    void addElem(Chronological c){
        int hour = c.getDate().getHour();
        if(this.hours[hour] == null) this.hours[hour] = new Hour();
        this.hours[hour].addElem(c);
    }

    boolean iterateForward(CalendarioPredicate<? extends Chronological> predicate){
        boolean r = true;
        for(int i = 0; r && i < 24; i++){
            if(this.hours[i] != null) r = this.hours[i].iterateForward(predicate);
        }
        return r;
    }

    boolean iterateBackwards(CalendarioPredicate<? extends Chronological> predicate){
        boolean r = true;
        for(int i = 23; r && i >= 0 ; i--){
            if(this.hours[i] != null) r = this.hours[i].iterateBackwards(predicate);
        }
        return r;
    }
}
