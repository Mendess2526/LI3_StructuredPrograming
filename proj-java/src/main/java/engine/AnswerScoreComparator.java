package engine;

import java.util.Comparator;

/**
 * Comparador do score das respostas.
 */
class AnswerScoreComparator implements Comparator<Answer> {


    /**
     * {@inheritDoc}
     */
    @Override
    public int compare(Answer answer1, Answer answer2){
        return Integer.compare(answer1.getScore(),answer2.getScore());
    }

}
