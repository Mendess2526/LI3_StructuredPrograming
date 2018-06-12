package engine.comparators;

import engine.Question;

import java.time.LocalDate;
import java.util.Comparator;

/**
 * Comparador do número de respostas das questões.
 */
public class QuestionAnswerCountComparator implements Comparator<Question> {

    private final LocalDate from;
    private final LocalDate to;

    public QuestionAnswerCountComparator(LocalDate from, LocalDate to){
        this.from = from;
        this.to = to;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public int compare(Question question1, Question question2){
        return Integer.compare(question1.getAnswerCountBetweenDate(this.from, this.to),
                               question2.getAnswerCountBetweenDate(this.from, this.to));
    }
}
