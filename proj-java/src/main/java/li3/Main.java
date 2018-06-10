package main.java.li3;

//import main.java.common.MyLog;

import main.java.common.Pair;
import main.java.engine.TCD;

import java.time.LocalDate;
import java.time.Month;
import java.util.Arrays;
import java.util.List;

public class Main {


    public static void main(String[] args){

        /*
            LOG CONFIGURATION
        */
        //MyLog log = new MyLog("results");
        //MyLog logtime = new MyLog("times");
        /* -------------------------------------------------------------------------------------------*/

        long before, after;
        TADCommunity qe = new TCD();
        long[] times = new long[13];
        int i = 0;
        /*
            LOAD PHASE
         */
        try{
            before = System.currentTimeMillis();
            qe.load(args[0]);
            after = System.currentTimeMillis();
            times[i++] = after-before;
        }catch(IndexOutOfBoundsException e){
            System.out.println("Deve passar o caminho do dump como argumento.");
            return;
        }

        /*
           Query 1
        */
        before = System.currentTimeMillis();
        Pair<String,String> q1 = qe.infoFromPost(801049);
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 1 -> " + q1);

        /*
           Query 2
        */
        before = System.currentTimeMillis();
        List<Long> q2 = qe.topMostActive(10);
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 2 -> " + q2);

        /*
           Query 3
        */
        before = System.currentTimeMillis();
        Pair<Long,Long> q3 = qe.totalPosts(LocalDate.of(2016, Month.JULY, 1),
                                           LocalDate.of(2016, Month.JULY, 31));
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 3 -> " + q3);

        /*
           Query 4
        */
        before = System.currentTimeMillis();
        List<Long> query4 = qe.questionsWithTag("package-management", LocalDate.of(2013, Month.MARCH, 1),
                                                LocalDate.of(2013, Month.MARCH, 31));
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 4 -> " + query4);

        /*
           Query 5
        */
        before = System.currentTimeMillis();
        Pair<String,List<Long>> q5 = qe.getUserInfo(15811);
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 5 -> " + q5);

        /*
           Query 6
        */
        before = System.currentTimeMillis();
        List<Long> q6 = qe.mostVotedAnswers(5, LocalDate.of(2015, Month.NOVEMBER, 1),
                                            LocalDate.of(2015, Month.NOVEMBER, 30));
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 6 -> " + q6);

        /*
           Query 7
        */
        before = System.currentTimeMillis();
        List<Long> q7 = qe.mostAnsweredQuestions(10, LocalDate.of(2014, Month.AUGUST, 1),
                                                 LocalDate.of(2014, Month.AUGUST, 10));
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 7 -> " + q7);

        /*
           Query 8
        */
        before = System.currentTimeMillis();
        List<Long> q8 = qe.containsWord(10, "kde");
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 8 -> " + q8);

        /*
           Query 9
        */
        before = System.currentTimeMillis();
        List<Long> q9 = qe.bothParticipated(10, 87, 5691);
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 9 -> " + q9);

        /*
           Query 10
        */
        before = System.currentTimeMillis();
        long q10 = qe.betterAnswer(30334);
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 10 -> " + q10);

        /*
            Query 11
        */
        before = System.currentTimeMillis();
        List<Long> q11 = qe.mostUsedBestRep(5, LocalDate.of(2013, Month.NOVEMBER, 1),
                                            LocalDate.of(2013, Month.NOVEMBER, 30));
//        List<Long> q11 = qe.mostUsedBestRep(5, LocalDate.MIN, LocalDate.MAX);
        after = System.currentTimeMillis();
        times[i++] = after-before;
        System.out.println("Query 11 -> " + q11);

        /*
            CLEAN PHASE
         */
        before = System.currentTimeMillis();
        qe.clear();
        after = System.currentTimeMillis();
        times[i] = after-before;

        i = 0;
        System.out.println("--------------------Times--------------------");
        for(long time : times) System.out.println(String.format("Query %2d: %d ms", i++, time));
        System.out.println("Total:    " + Arrays.stream(times).sum()+ " ms");

    }

}


