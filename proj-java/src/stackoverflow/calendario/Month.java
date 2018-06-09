package stackoverflow.calendario;

import java.time.LocalDate;

@SuppressWarnings("Duplicates")
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
        int fromD;
        int toD;
        if(ip == IterPoint.IS_BOTH){
            fromD = from.getDayOfMonth() - 1;
            toD = to.getDayOfMonth() - 1;
        }else if(ip == IterPoint.IS_START){
            fromD = from.getDayOfMonth() - 1;
            toD = nrDays(to.getMonthValue()) - 1;
        }else if(ip == IterPoint.IS_END){
            fromD = 0;
            toD = to.getDayOfMonth() - 1;
        }else{
            fromD = 0;
            toD = nrDays(to.getMonthValue()) - 1;
        }
        boolean keepGoing = true;
        for(int i = fromD; keepGoing && i <= toD; i++){
            Day<T> d = this.days.get(i);
            if(d != null) keepGoing = d.iterateForward(predicate);
        }
        return keepGoing;
    }

    boolean iterateBackwards(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<T> predicate){
        int fromD;
        int toD;
        if(ip == IterPoint.IS_BOTH){
            fromD = from.getDayOfMonth() - 1;
            toD = to.getDayOfMonth() - 1;
        }else if(ip == IterPoint.IS_START){
            fromD = from.getDayOfMonth() - 1;
            toD = 0;
        }else if(ip == IterPoint.IS_END){
            fromD = nrDays(to.getMonthValue()) - 1;
            toD = to.getDayOfMonth() - 1;
        }else{
            fromD = nrDays(to.getMonthValue()) - 1;
            toD = 0;
        }
        boolean keepGoing = true;
        for(int i = fromD; keepGoing && i >= toD; i--){
            Day<T> d = this.days.get(i);
            if(d != null) keepGoing = d.iterateBackwards(predicate);
        }
        return keepGoing;
    }

    long countElements(LocalDate from, LocalDate to, IterPoint ip){
        int fromD;
        int toD;
        if(ip == IterPoint.IS_BOTH){
            fromD = from.getDayOfMonth() - 1;
            toD = to.getDayOfMonth() - 1;
        }else if(ip == IterPoint.IS_START){
            fromD = from.getDayOfMonth() - 1;
            toD = nrDays(to.getMonthValue()) - 1;
        }else if(ip == IterPoint.IS_END){
            fromD = 0;
            toD = to.getDayOfMonth() - 1;
        }else{
            fromD = 0;
            toD = nrDays(to.getMonthValue()) - 1;
        }
        long count = 0;
        for(int i = fromD; i <= toD; i++){
            Day<T> d = this.days.get(i);
            if(d != null) count += d.countElements();
        }
        return count;
    }
}
