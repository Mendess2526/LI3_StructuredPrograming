package stackoverflow;

import java.util.Comparator;

public class AnswerScoreComparator implements Comparator<Answer> {

    @Override
    public int compare(Answer answer1, Answer answer2){
        return Integer.compare(answer1.getScore(),answer2.getScore());
    }

}
