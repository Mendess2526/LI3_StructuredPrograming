package stackoverflow.calendario;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;

public class Calendario<T extends Chronological> {

    private Map<Integer,Year<T>> years;

    public Calendario(){
        this.years = new HashMap<>();
    }

    public void addElem(T c){
        Year<T> y = this.years.get(c.getDate().getYear());
        if(y == null){
            y = new Year<>();
            this.years.put(c.getDate().getYear(), y);
        }
        y.addElem(c);
    }

    public void iterate(LocalDate from, LocalDate to, CalendarioPredicate<T> predicate){
        if(from.isBefore(to))
            iterateForward(from, to, predicate);
        else iterateBackwards(from, to, predicate);
    }

    private void iterateForward(LocalDate from, LocalDate to, CalendarioPredicate<T> predicate){
        int fromY = from.getYear();
        int toY = to.getYear();
        if(fromY <= toY){
            Year<T> y = this.years.get(fromY);
            if(y!=null
               && !y.iterateForward(from, to, IterPoint.make(true, fromY == toY),predicate))
                return;
        }
        while(fromY <= toY){
            Year<T> y = this.years.get(fromY);
            if(y!=null
               && !y.iterateForward(from, to, IterPoint.make(false, fromY == toY), predicate))
                return;
        }
    }

    private void iterateBackwards(LocalDate from, LocalDate to, CalendarioPredicate<T> predicate){
        int fromY = from.getYear();
        int toY = to.getYear();
        if(fromY >= toY){
            Year<T> y = this.years.get(fromY);
            if(y!=null
                    && !y.iterateBackwards(from, to, IterPoint.make(true, fromY == toY),predicate))
                return;
        }
        while(fromY >= toY){
            Year<T> y = this.years.get(fromY);
            if(y!=null
                    && !y.iterateBackwards(from, to, IterPoint.make(false, fromY == toY), predicate))
                return;
        }
    }
}
