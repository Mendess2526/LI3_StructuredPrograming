package stackoverflow;

import java.util.Comparator;

public class AnswerDateComparator implements Comparator<Answer> {

    public int compare(Answer answer1, Answer answer2){
        return answer1.getDate().compareTo(answer2.getDate()); }
}
