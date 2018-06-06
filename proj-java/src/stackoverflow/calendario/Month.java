package stackoverflow.calendario;

import java.time.LocalDate;

class Month<T extends Chronological> {
    private FixedSizeList<Day<T>> days;

    Month(int month){
        this.days = new FixedSizeList<>(nrDays(month));
    }

    private int nrDays(int m){
        if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
        if(m == 1 ) return 29;
        return 31;
    }

    void addElem(T c){
        int day = c.getDate().getDayOfMonth() - 1;
        if(this.days.get(day) == null) this.days.set(day, new Day<>());
        this.days.get(day).addElem(c);
    }

    boolean iterateForward(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<T> predicate){
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
                toD = nrDays(to.getMonthValue()) - 1;
                break;
            case IS_END:
                fromD = 0;
                toD = to.getDayOfMonth() - 1;
                break;
            case IS_NEITHER:
                fromD = 0;
                toD = nrDays(to.getMonthValue()) - 1;
                break;
            default: assert false; return false;
        }
        for(int i = fromD; r && i < toD; i++){
            if(this.days.get(i) != null) r = this.days.get(i).iterateForward(predicate);
        }
        return r;
    }

    boolean iterateBackwards(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<T> predicate){
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
                toD = 0;
                break;
            case IS_END:
                fromD = nrDays(to.getMonthValue()) - 1;
                toD = to.getDayOfMonth() - 1;
                break;
            case IS_NEITHER:
                fromD = nrDays(to.getMonthValue()) - 1;
                toD = 0;
                break;
            default: assert false; return false;
        }
        for(int i = fromD; r && i > toD; i--){
            if(this.days.get(i) != null) r = this.days.get(i).iterateBackwards(predicate);
        }
        return r;
    }

    long countElements(LocalDate from, LocalDate to, IterPoint ip){
        int fromD;
        int toD;
        switch(ip){
            case IS_BOTH:
                fromD = from.getDayOfMonth() - 1;
                toD = to.getDayOfMonth() - 1;
                break;
            case IS_START:
                fromD = from.getDayOfMonth() - 1;
                toD = nrDays(to.getMonthValue()) - 1;
                break;
            case IS_END:
                fromD = 0;
                toD = to.getDayOfMonth() - 1;
                break;
            case IS_NEITHER:
                fromD = 0;
                toD = nrDays(to.getMonthValue()) - 1;
                break;
            default: assert false; return Long.MIN_VALUE;
        }
        long count = 0;
        for(int i = fromD; i < toD; i++){
            if(this.days.get(i) != null) count += this.days.get(i).countElements();
        }
        return count;
    }
}
