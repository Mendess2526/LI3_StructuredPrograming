package stackoverflow.calendario;

import java.time.LocalDate;

@SuppressWarnings("BooleanMethodIsAlwaysInverted")
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

    boolean iterateForward(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<T> predicate){
        boolean r = true;
        int fromM;
        int toM;
        switch(ip){
            case IS_BOTH:
                fromM = from.getMonthValue() - 1;
                toM = to.getMonthValue() - 1;
                break;
            case IS_START:
                fromM = from.getMonthValue() - 1;
                toM = 11;
                break;
            case IS_END:
                fromM = 0;
                toM = to.getMonthValue() - 1;
                break;
            case IS_NEITHER:
                fromM = 0;
                toM = 0;
                break;
            default: assert false; return false;
        }
        if(ip == IterPoint.IS_START && fromM <= toM){
            Month<T> m = this.months.get(fromM);
            if(m != null && !m.iterateForward(
                    from,
                    to,
                    IterPoint.make(true,ip.isEnd && fromM == toM),
                    predicate))
                return false;
            fromM++;
        }
        while(r && fromM <= toM){
            Month<T> m = this.months.get(fromM);
            if(m != null)
                r = m.iterateForward(
                        from,
                        to,
                        IterPoint.make(false,ip.isEnd && fromM == toM),
                        predicate);
            fromM++;
        }
        return r;
    }

    boolean iterateBackwards(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<T> predicate){
        boolean r = true;
        int fromM;
        int toM;
        switch(ip){
            case IS_BOTH:
                fromM = from.getMonthValue() - 1;
                toM = to.getMonthValue() - 1;
                break;
            case IS_START:
                fromM = from.getMonthValue() - 1;
                toM = 0;
                break;
            case IS_END:
                fromM = 11;
                toM = to.getMonthValue() - 1;
                break;
            case IS_NEITHER:
                fromM = 11;
                toM = 0;
                break;
            default: assert false; return false;
        }
        if(ip == IterPoint.IS_START && fromM >= toM){
            Month<T> m = this.months.get(fromM);
            if(m != null && !m.iterateBackwards(
                    from,
                    to,
                    IterPoint.make(true,ip.isEnd && fromM == toM),
                    predicate))
                return false;
            fromM--;
        }
        while(r && fromM >= toM){
            Month<T> m = this.months.get(fromM);
            if(m != null)
                r = m.iterateBackwards(
                        from,
                        to,
                        IterPoint.make(false,ip.isEnd && fromM == toM),
                        predicate);
            fromM--;
        }
        return r;
    }

    public long countElements(LocalDate from, LocalDate to, IterPoint ip){
        int fromM;
        int toM;
        switch(ip){
            case IS_BOTH:
                fromM = from.getMonthValue() - 1;
                toM = to.getMonthValue() - 1;
                break;
            case IS_START:
                fromM = from.getMonthValue() - 1;
                toM = 11;
                break;
            case IS_END:
                fromM = 0;
                toM = to.getMonthValue() - 1;
                break;
            case IS_NEITHER:
                fromM = 0;
                toM = 0;
                break;
            default: assert false; return Long.MIN_VALUE;
        }
        long count = 0;
        if(ip == IterPoint.IS_START && fromM <= toM){
            count += this.months.get(fromM++).countElements(
                    from,
                    to,
                    IterPoint.make(true,ip.isEnd && fromM == toM));
        }
        while(fromM <= toM){
            Month<T> m = this.months.get(fromM++);
            if(m != null)
                count += m.countElements(
                        from,
                        to,
                        IterPoint.make(false,ip.isEnd && fromM == toM));
            fromM++;
        }
        return count;
    }
}