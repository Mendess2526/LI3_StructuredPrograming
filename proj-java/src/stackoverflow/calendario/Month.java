package stackoverflow.calendario;

import java.time.LocalDate;

class Month {
    private Day[] days;

    Month(int month){
        this.days = new Day[nrDays(month)];
    }

    private int nrDays(int m){
        if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
        if(m == 1 ) return 29;
        return 31;
    }

    void addElem(Chronological c){
        int day = c.getDate().getDayOfMonth() - 1;
        if(this.days[day] == null) this.days[day] = new Day();
        this.days[day].addElem(c);
    }

    boolean iterateForward(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<? extends Chronological> predicate){
        boolean r = true;
        int fromD;
        int toD;
        switch(ip){
            case IS_BOTH:
                fromD = from.getDayOfMonth() - 1;
                toD = to.getDayOfMonth() - 1;
                break;
            case IS_START:
                fromD = from.getDayOfMonth() - 1;
                toD = this.days.length - 1;
                break;
            case IS_END:
                fromD = 0;
                toD = to.getDayOfMonth() - 1;
                break;
            case IS_NEITHER:
                fromD = 0;
                toD = this.days.length - 1;
                break;
            default: assert false; return false;
        }
        for(int i = fromD; r && i < toD; i++){
            if(this.days[i] != null) r = this.days[i].iterateForward(predicate);
        }
        return r;
    }
}
