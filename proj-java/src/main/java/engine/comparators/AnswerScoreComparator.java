package engine.comparators;

import engine.Answer;

import java.util.Comparator;

/**
 * Comparador do score das respostas.
 */
public class AnswerScoreComparator implements Comparator<Answer> {


    /**
     * {@inheritDoc}
     */
    @Override
    public int compare(Answer answer1, Answer answer2){
        return Integer.compare(answer1.getScore(), answer2.getScore());
    }

}
