package main.java.engine.calendario;

import main.java.engine.collections.FixedSizeList;

import java.time.LocalDate;
import java.util.function.Predicate;

@SuppressWarnings({"BooleanMethodIsAlwaysInverted", "Duplicates"})
class Year<T extends Chronological> {
    private FixedSizeList<Month<T>> months;

    Year(){
        this.months = new FixedSizeList<>(12);
    }

    void addElem(T c){
        int month = c.getDate().getMonthValue() - 1;
        if(this.months.get(month) == null) this.months.set(month, new Month<>(month));
        this.months.get(month).addElem(c);
    }

    boolean iterateForward(LocalDate from, LocalDate to, IterPoint ip, Predicate<T> predicate){
        int fromM;
        int toM;
        if(ip == IterPoint.IS_BOTH){
            fromM = from.getMonthValue() - 1;
            toM = to.getMonthValue() - 1;
        }else if(ip == IterPoint.IS_START){
            fromM = from.getMonthValue() - 1;
            toM = 11;
        }else if(ip == IterPoint.IS_END){
            fromM = 0;
            toM = to.getMonthValue() - 1;
        }else{
            fromM = 0;
            toM = 0;
        }
        boolean keepGoing = true;
        if(ip.isStart && fromM <= toM){
            IterPoint newIp = IterPoint.make(true,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) keepGoing = m.iterateForward(from, to, newIp, predicate);
        }
        while(keepGoing && fromM <= toM){
            IterPoint newIP = IterPoint.make(false,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) keepGoing = m.iterateForward(from, to, newIP, predicate);
        }
        return keepGoing;
    }

    boolean iterateBackwards(LocalDate from, LocalDate to, IterPoint ip, Predicate<T> predicate){
        int fromM;
        int toM;
        if(ip == IterPoint.IS_BOTH){
            fromM = from.getMonthValue() - 1;
            toM = to.getMonthValue() - 1;
        }else if(ip == IterPoint.IS_START){
            fromM = from.getMonthValue() - 1;
            toM = 0;
        }else if(ip == IterPoint.IS_END){
            fromM = 11;
            toM = to.getMonthValue() - 1;
        }else{
            fromM = 11;
            toM = 0;
        }
        boolean keepGoing = true;
        if(ip.isStart && fromM >= toM){
            IterPoint newIp = IterPoint.make(true,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM--);
            if(m != null) keepGoing = m.iterateBackwards(from, to, newIp, predicate);
        }
        while(keepGoing && fromM >= toM){
            IterPoint newIp = IterPoint.make(false,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM--);
            if(m != null) keepGoing = m.iterateBackwards(from, to, newIp, predicate);
        }
        return keepGoing;
    }

    long countElements(LocalDate from, LocalDate to, IterPoint ip){
        int fromM;
        int toM;
        if(ip == IterPoint.IS_BOTH){
            fromM = from.getMonthValue() - 1;
            toM = to.getMonthValue() - 1;
        }else if(ip == IterPoint.IS_START){
            fromM = from.getMonthValue() - 1;
            toM = 11;
        }else if(ip == IterPoint.IS_END){
            fromM = 0;
            toM = to.getMonthValue() - 1;
        }else{
            fromM = 0;
            toM = 0;
        }
        long count = 0;
        if(ip.isStart && fromM <= toM){
            IterPoint newIp = IterPoint.make(true,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) count += m.countElements(from, to, newIp);
        }
        while(fromM <= toM){
            IterPoint newIp = IterPoint.make(false,ip.isEnd && fromM == toM);
            Month<T> m = this.months.get(fromM++);
            if(m != null) count += m.countElements(from, to, newIp);
            fromM++;
        }
        return count;
    }
}