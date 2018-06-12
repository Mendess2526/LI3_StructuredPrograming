package li3;

import common.Pair;
import engine.TCD;
import view.View;

import java.time.LocalDate;
import java.time.Month;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.List;
import java.util.stream.Collectors;

import static java.util.Arrays.asList;
import static java.util.Collections.singletonList;

public class Controller {

    private final TADCommunity com;
    private final View view;
    private boolean loaded = false;
    private String dumpPath;

    private Controller(TADCommunity com, View view){
        this.com = com;
        this.view = view;
    }

    public static void main(String[] args){
        new Controller(new TCD(), new View()).run(args);
    }

    private void run(String[] args){
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
                    pickQueryDefault();
                    break;
                case 3:
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
            if(this.com instanceof TCD){
                TCD com = (TCD) this.com;
                this.view.showEntityCounts(com.getUserCount(), com.getQuestionCount(), com.getAnswerCount());
            }
        }
    }

    private void pickQueryDefault(){
        boolean keepGoing = true;
        while(keepGoing){
            int i = this.view.runPickQueryMenu();
            if(i != 0){
                switch(i){
                    case 1:
                        queryHandler(i, runQuery1());
                        break;
                    case 2:
                        queryHandler(i, runQuery2());
                        break;
                    case 3:
                        queryHandler(i, runQuery3());
                        break;
                    case 4:
                        queryHandler(i, runQuery4());
                        break;
                    case 5:
                        queryHandler(i, runQuery5());
                        break;
                    case 6:
                        queryHandler(i, runQuery6());
                        break;
                    case 7:
                        queryHandler(i, runQuery7());
                        break;
                    case 8:
                        queryHandler(i, runQuery8());
                        break;
                    case 9:
                        queryHandler(i, runQuery9());
                        break;
                    case 10:
                        queryHandler(i, runQuery10());
                        break;
                    case 11:
                        queryHandler(i, runQuery11());
                        break;
                }
                this.view.requestContinue();
            }else{
                keepGoing = false;
            }
        }
    }

    private void pickQuery(){
        boolean keepGoing = true;
        while(keepGoing){
            int i = this.view.runPickQueryMenu();
            List<String> results;
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
            if(i != 0){
                try{
                    switch(i){
                        case 1:
                            results = this.view.runForm(singletonList("Id: "));
                            queryHandler(i, runQuery1(Integer.parseInt(results.get(0))));
                            break;
                        case 2:
                            results = this.view.runForm(singletonList("N: "));
                            queryHandler(i, runQuery2(Integer.parseInt(results.get(0))));
                            break;
                        case 3:
                            results = this.view.runForm(asList("Begin date (yyyy-MM-dd): ", "End date (yyyy-MM-dd): "));
                            queryHandler(i, runQuery3(LocalDate.parse(results.get(0), formatter),
                                                      LocalDate.parse(results.get(1), formatter)));
                            break;
                        case 4:
                            results = this.view.runForm(
                                    asList("Tag: ", "Begin date (yyyy-MM-dd): ", "End date (yyyy-MM-dd)"));
                            queryHandler(i, runQuery4(results.get(0), LocalDate.parse(results.get(1), formatter),
                                                      LocalDate.parse(results.get(2), formatter)));
                            break;
                        case 5:
                            results = this.view.runForm(singletonList("Id: "));
                            queryHandler(i, runQuery5(Long.parseLong(results.get(0))));
                            break;
                        case 6:
                            results = this.view.runForm(
                                    asList("N: ", "Begin date (yyyy-MM-dd): ", "End date (yyyy-MM-dd)"));
                            queryHandler(i, runQuery6(Integer.parseInt(results.get(0)),
                                                      LocalDate.parse(results.get(1), formatter),
                                                      LocalDate.parse(results.get(2), formatter)));
                            break;
                        case 7:
                            results = this.view.runForm(
                                    asList("N: ", "Begin date (yyyy-MM-dd): ", "End date (yyyy-MM-dd)"));
                            queryHandler(i, runQuery7(Integer.parseInt(results.get(0)),
                                                      LocalDate.parse(results.get(1), formatter),
                                                      LocalDate.parse(results.get(2), formatter)));
                            break;
                        case 8:
                            results = this.view.runForm(asList("N: ", "Word: "));
                            queryHandler(i, runQuery8(Integer.parseInt(results.get(0)), results.get(1)));
                            break;
                        case 9:
                            results = this.view.runForm(asList("N: ", "Id1: ", "Id2: "));
                            List<Long> r = results.stream().map(Long::parseLong).collect(Collectors.toList());
                            queryHandler(i, runQuery9(Math.toIntExact(r.get(0)), r.get(1), r.get(2)));
                            break;
                        case 10:
                            results = this.view.runForm(singletonList("Id: "));
                            queryHandler(i, runQuery10(Long.parseLong(results.get(0))));
                            break;
                        case 11:
                            results = this.view.runForm(
                                    asList("N: ", "Begin date (yyyy-MM-dd): ", "End date (yyyy-MM-dd)"));
                            queryHandler(i, runQuery11(Integer.parseInt(results.get(0)),
                                                       LocalDate.parse(results.get(1), formatter),
                                                       LocalDate.parse(results.get(2), formatter)));
                            break;
                    }
                }catch(NumberFormatException | DateTimeParseException e){
                    this.view.apresentarErro("Parametro invalido: ", e.getMessage());
                }
                this.view.requestContinue();
            }else{
                keepGoing = false;
            }
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
        int i = 1;
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
        queryHandler(i, runQuery11());
        this.view.requestContinue();
    }

    private void queryHandler(int i, InputOutputTime<Long,?,?> r){
        this.view.showResults(i, r.input, r.output, r.time);
    }

    private InputOutputTime<Long,String,String> runQuery0() throws NullPointerException{
        long before = System.currentTimeMillis();
        this.com.load(this.dumpPath);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, singletonList(this.dumpPath), "done");
    }

    private InputOutputTime<Long,Long,Pair<String,String>> runQuery1(){
        return runQuery1(801049);
    }

    private InputOutputTime<Long,Long,Pair<String,String>> runQuery1(long id){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        Pair<String,String> r = this.com.infoFromPost(id);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, singletonList(id), r);
    }

    private InputOutputTime<Long,Integer,List<Long>> runQuery2(){
        return runQuery2(10);
    }

    private InputOutputTime<Long,Integer,List<Long>> runQuery2(int n){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        List<Long> r = this.com.topMostActive(n);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, singletonList(n), r);
    }

    private InputOutputTime<Long,LocalDate,Pair<Long,Long>> runQuery3(){
        return runQuery3(LocalDate.of(2016, Month.JULY, 1), LocalDate.of(2016, Month.JULY, 31));
    }

    private InputOutputTime<Long,LocalDate,Pair<Long,Long>> runQuery3(LocalDate begin, LocalDate end){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        Pair<Long,Long> r = this.com.totalPosts(begin, end);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, asList(begin, end), r);
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery4(){
        return runQuery4("package-management", LocalDate.of(2013, Month.MARCH, 1), LocalDate.of(2013, Month.MARCH, 31));
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery4(String tag, LocalDate begin, LocalDate end){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        List<Long> r = this.com.questionsWithTag(tag, begin, end);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, asList(tag, begin, end), r);
    }

    private InputOutputTime<Long,Long,Pair<String,List<Long>>> runQuery5(){
        return runQuery5(15811);
    }

    private InputOutputTime<Long,Long,Pair<String,List<Long>>> runQuery5(long id){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        Pair<String,List<Long>> r = this.com.getUserInfo(id);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, singletonList(id), r);

    }

    private InputOutputTime<Long,Object,List<Long>> runQuery6(){
        return runQuery6(5, LocalDate.of(2015, Month.NOVEMBER, 1), LocalDate.of(2015, Month.NOVEMBER, 30));
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery6(int n, LocalDate begin, LocalDate end){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        List<Long> r = this.com.mostVotedAnswers(n, begin, end);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, asList(n, begin, end), r);
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery7(){
        return runQuery7(10, LocalDate.of(2014, Month.AUGUST, 1), LocalDate.of(2014, Month.AUGUST, 10));
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery7(int n, LocalDate begin, LocalDate end){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        List<Long> r = this.com.mostAnsweredQuestions(n, begin, end);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, asList(10, begin, end), r);
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery8(){
        return runQuery8(10, "kde");
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery8(int n, String word){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        List<Long> r = this.com.containsWord(n, word);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, asList(n, word), r);
    }

    private InputOutputTime<Long,Long,List<Long>> runQuery9(){
        return runQuery9(10, 87, 5691);
    }

    private InputOutputTime<Long,Long,List<Long>> runQuery9(int n, long id1, long id2){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        List<Long> r = this.com.bothParticipated(n, id1, id2);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, asList((long) n, id1, id2), r);
    }

    private InputOutputTime<Long,Long,Long> runQuery10(){
        return runQuery10(30334L);
    }

    private InputOutputTime<Long,Long,Long> runQuery10(long id){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        long r = this.com.betterAnswer(id);
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, singletonList(id), r);
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery11(){
        return runQuery11(5, LocalDate.of(2013, Month.NOVEMBER, 1), LocalDate.of(2013, Month.NOVEMBER, 30));
    }

    private InputOutputTime<Long,Object,List<Long>> runQuery11(int n, LocalDate begin, LocalDate end){
        loadIfNeeded();
        long before = System.currentTimeMillis();
        List<Long> r = this.com.mostUsedBestRep(n, begin, end).stream().sorted().collect(Collectors.toList());
        long after = System.currentTimeMillis();
        return new InputOutputTime<>(after - before, asList(n, begin, end), r);
    }

    private class InputOutputTime<T, I, O> {

        private final List<I> input;
        private final O output;
        private final T time;

        private InputOutputTime(T time, List<I> input, O output){
            this.input = input;
            this.output = output;
            this.time = time;
        }
    }
}


