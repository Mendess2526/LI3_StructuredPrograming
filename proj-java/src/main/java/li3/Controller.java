package li3;

import common.Pair;
import view.View;

import java.time.LocalDate;
import java.time.Month;
import java.util.List;

public class Controller {

    private TADCommunity com;
    private View view;
    private boolean loaded = false;
    private String dumpPath;

    Controller(TADCommunity com, View view){
        this.com = com;
        this.view = view;
    }

    void run(String[] args){
        boolean keepGoing = true;
        while(keepGoing){
            int i = this.view.runMainMenu();
            switch(i){
                case 1: // All queries
                    getDumpPath(args);
                    runAllQueries();
                    break;
                case 2:
                    getDumpPath(args);
                    pickQuery();
                    break;
                default:
                    keepGoing = false;
            }
        }
    }

    private void loadIfNeeded(){
        if(!this.loaded){
            this.view.notifyLoading();
            queryHandler(0, runQuery0());
            this.loaded = true;
        }
    }

    private void pickQuery(){
        int i = this.view.runPickQueryMenu();
        if(i != 0) loadIfNeeded();
        switch(i){
            case 1: queryHandler(i, runQuery1()); break;
            case 2: queryHandler(i, runQuery2()); break;
            case 3: queryHandler(i, runQuery3()); break;
            case 4: queryHandler(i, runQuery4()); break;
            case 5: queryHandler(i, runQuery5()); break;
            case 6: queryHandler(i, runQuery6()); break;
            case 7: queryHandler(i, runQuery7()); break;
            case 8: queryHandler(i, runQuery8()); break;
            case 9: queryHandler(i, runQuery9()); break;
            case 10: queryHandler(i, runQuery10()); break;
            case 11: queryHandler(i, runQuery11()); break;
        }
    }

    private void getDumpPath(String[] args){
        if(args.length == 0){
            this.dumpPath = this.view.requestDumpPath();
        }else{
            this.dumpPath = args[0];
        }
    }

    private void runAllQueries(){
        int i = 0;
        loadIfNeeded();
        queryHandler(i++, runQuery1());
        queryHandler(i++, runQuery2());
        queryHandler(i++, runQuery3());
        queryHandler(i++, runQuery4());
        queryHandler(i++, runQuery5());
        queryHandler(i++, runQuery6());
        queryHandler(i++, runQuery7());
        queryHandler(i++, runQuery8());
        queryHandler(i++, runQuery9());
        queryHandler(i++, runQuery10());
        queryHandler(i,   runQuery11());
    }

    private void queryHandler(int i , Pair<Long, ?> r){
        this.view.showResults(i, r.getSnd(), r.getFst());
    }

    private Pair<Long , String> runQuery0() throws NullPointerException{
        long before = System.currentTimeMillis();
        this.com.load(this.dumpPath);
        long after = System.currentTimeMillis();
        return new Pair<>(after-before, "done");
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


