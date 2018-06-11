package li3;

import common.Pair;
import engine.TCD;

import java.time.LocalDate;
import java.time.Month;
import java.util.List;

public class Controller {

    private TADCommunity com;
    private View view;

    public static void main(String[] args){
        new Controller(new TCD(), new View()).run(args);
    }

    private Controller(TADCommunity com, View view){
        this.com = com;
        this.view = view;
    }

    private void run(String[] args){

    }

    private long runQuery0(String path) throws NullPointerException{
            long before = System.currentTimeMillis();
            this.com.load(path);
            long after = System.currentTimeMillis();
            return after-before;
    }

    private Pair<Long,Pair<String, String>> runQuery1(){
        long before = System.currentTimeMillis();
        Pair<String,String> r = this.com.infoFromPost(801049);
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long, List<Long>> runQuery2(){
        long before = System.currentTimeMillis();
        List<Long> r = this.com.topMostActive(10);
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }
    
    private Pair<Long, Pair<Long,Long>> runQuery3(){
        long before = System.currentTimeMillis();
        Pair<Long,Long> r = this.com.totalPosts(LocalDate.of(2016, Month.JULY, 1),
                                           LocalDate.of(2016, Month.JULY, 31));
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long,List<Long>> runQuery4(){
        long before = System.currentTimeMillis();
        List<Long> r = this.com.questionsWithTag("package-management", LocalDate.of(2013, Month.MARCH, 1),
                                                LocalDate.of(2013, Month.MARCH, 31));
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long,Pair<String,List<Long>>> runQuery5(){
        long before = System.currentTimeMillis();
        Pair<String,List<Long>> r = this.com.getUserInfo(15811);
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);

    }

    private Pair<Long,List<Long>> runQuery6(){
        long before = System.currentTimeMillis();
        List<Long> r = this.com.mostVotedAnswers(5, LocalDate.of(2015, Month.NOVEMBER, 1),
                                            LocalDate.of(2015, Month.NOVEMBER, 30));
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long,List<Long>> runQuery7(){
        long before = System.currentTimeMillis();
        List<Long> r = this.com.mostAnsweredQuestions(10, LocalDate.of(2014, Month.AUGUST, 1),
                                                 LocalDate.of(2014, Month.AUGUST, 10));
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long,List<Long>> runQuery8(){
        long before = System.currentTimeMillis();
        List<Long> r = this.com.containsWord(10, "kde");
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long,List<Long>> runQuery9(){
        long before = System.currentTimeMillis();
        List<Long> r = this.com.bothParticipated(10, 87, 5691);
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long,Long> runQuery10(){
        long before = System.currentTimeMillis();
        long r = this.com.betterAnswer(30334);
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }

    private Pair<Long,List<Long>> runQuery11(){
        long before = System.currentTimeMillis();
        List<Long> r = this.com.mostUsedBestRep(5, LocalDate.of(2013, Month.NOVEMBER, 1),
                                            LocalDate.of(2013, Month.NOVEMBER, 30));
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, r);
    }
}


