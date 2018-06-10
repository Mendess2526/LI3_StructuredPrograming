package main.java.engine;

import java.util.Comparator;

public class QuestionAnswerCountComparator implements Comparator<Question>{

    @Override
    public int compare(Question question1, Question question2){
        return Integer.compare(question1.getAnswerCount(), question2.getAnswerCount());
    }
}
