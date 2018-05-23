package stackoverflow.calendario;

import java.time.LocalDate;

class Year<T extends Chronological> {
    private Month[] months;

    Year(){
        this.months = new Month[12];
    }

    void addElem(T c){
        int month = c.getDate().getMonthValue() - 1;
        if(this.months[month] == null) this.months[month] = new Month(month);
        this.months[month].addElem(c);
    }

    boolean iterateForward(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<? extends Chronological> predicate){
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
            if(!this.months[fromM++].iterateForward(
                    from,
                    to,
                    IterPoint.make(true,ip.isEnd && fromM == toM),
                    predicate))
                return false;
        }
        while(r && fromM <= toM){
            if(this.months[fromM] != null)
                r = this.months[fromM++].iterateForward(
                        from,
                        to,
                        IterPoint.make(false,ip.isEnd && fromM == toM),
                        predicate);
        }
        return r;
    }



    boolean iterateBackwards(LocalDate from, LocalDate to, IterPoint ip, CalendarioPredicate<? extends Chronological> predicate){
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
            if(!this.months[fromM--].iterateBackwards(
                    from,
                    to,
                    IterPoint.make(true,ip.isEnd && fromM == toM),
                    predicate))
                return false;
        }
        while(r && fromM >= toM){
            if(this.months[fromM] != null)
                r = this.months[fromM--].iterateBackwards(
                        from,
                        to,
                        IterPoint.make(false,ip.isEnd && fromM == toM),
                        predicate);
        }
        return r;
    }






}