package engine.calendario;

import java.time.LocalDate;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Predicate;

public class Calendario<T extends Chronological> {

    private final Map<Integer,Year<T>> years;

    public Calendario(){
        this.years = new HashMap<>();
    }

    public void addElem(T c){
        this.years.computeIfAbsent(c.getDate().getYear(), k->new Year<>()).addElem(c);
    }

    public void iterate(LocalDate from, LocalDate to, Predicate<T> predicate){
        if(from.isBefore(to)) iterateForward(from, to, predicate);
        else iterateBackwards(from, to, predicate);
    }

    private void iterateForward(LocalDate from, LocalDate to, Predicate<T> predicate){
        int fromY = from.getYear();
        int toY = to.getYear();
        boolean keepGoing = true;
        if(fromY <= toY){
            IterPoint ip = IterPoint.make(true, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y!=null) keepGoing = y.iterateForward(from, to, ip, predicate);
        }
        while(keepGoing && fromY <= toY){
            IterPoint ip = IterPoint.make(false, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y!=null) keepGoing = y.iterateForward(from, to, ip, predicate);
        }
    }

    private void iterateBackwards(LocalDate from, LocalDate to, Predicate<T> predicate){
        int fromY = from.getYear();
        int toY = to.getYear();
        boolean keepGoing = true;
        if(fromY >= toY){
            IterPoint ip = IterPoint.make(true, fromY == toY);
            Year<T> y = this.years.get(fromY--);
            if(y!=null) keepGoing = y.iterateBackwards(from, to, ip, predicate);
        }
        while(keepGoing && fromY >= toY){
            IterPoint ip = IterPoint.make(false, fromY == toY);
            Year<T> y = this.years.get(fromY--);
            if(y!=null) keepGoing = y.iterateBackwards(from, to, ip, predicate);
        }
    }

    public long countElements(LocalDate from, LocalDate to){
        if(from.isAfter(to)){
            LocalDate tmp = from;
            from = to;
            to = tmp;
        }
        int fromY = from.getYear();
        int toY = to.getYear();
        long count = 0;
        if(fromY <= toY){
            IterPoint ip = IterPoint.make(true, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y != null) count = y.countElements(from, to, ip);
        }
        while(fromY <= toY){
            IterPoint ip = IterPoint.make(false, fromY == toY);
            Year<T> y = this.years.get(fromY++);
            if(y!=null) count += y.countElements(from, to, ip);
        }
        return count;
    }
}
