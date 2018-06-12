package engine;

import java.util.Comparator;

/**
 * Comparador do número de respostas das questões.
 */
class QuestionAnswerCountComparator implements Comparator<Question>{

    /**
     * {@inheritDoc}
     */
    @Override
    public int compare(Question question1, Question question2){
        return Integer.compare(question1.getAnswerCount(), question2.getAnswerCount());
    }
}
