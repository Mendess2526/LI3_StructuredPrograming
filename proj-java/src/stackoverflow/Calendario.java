package stackoverflow;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

class Calendario<T> {

    private class Hour{
        int count;
        SortedLinkedList<Chronological> elems;
        private Hour(){
            this.count = 0;
            elems = new SortedLinkedList<>();
        }
        private void addElem(Chronological c){
            this.elems.addLast(c , Comparator.comparing(Chronological::getDate));
        }
    }
    private class Day{
        Calendario.Hour[] hours;
        private Day(){
            this.hours = new Calendario.Hour[24];
        }
        private void addElem(Chronological c){
            int day = c.getDate().getDayOfMonth();
            if(this.hours[day] == null) this.hours[day] = new Hour();
            this.hours[day].addElem(c);
        }
    }
    private class Month{
        int nDays;
        Calendario.Day[] days;
        private Month(int month){
            this.nDays = nrDays(month);
            this.days = new Calendario.Day[this.nDays];
        }
        private int nrDays(int m){
            if(m == 3 || m == 5 || m == 8 || m == 10) return 30;
            if(m == 1 ) return 29;
            return 31;
        }
    }
    private class Year{
        Calendario.Month[] months;
        private Year(){
            this.months = new Calendario.Month[12];
        }
    }
    private Map<Integer, Year> years;

    public Calendario(){
        this.years = new HashMap<>();
    }

    public void addElem(Chronological c){
        Year y = this.years.get(c.getDate().getYear());
        if(y == null){
            y = new Year();
            this.years.put(c.getDate().getYear(), y);
        }
        //TODO add to y
    }
}
