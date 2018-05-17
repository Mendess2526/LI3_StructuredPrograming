package stackoverflow;

import java.time.LocalDateTime;
import java.util.LinkedList;

public class Question extends Post{
    private int answerCount;
    private String title;
    private String tags;
    private LinkedList<Answer> answers;

    public Question(long id, LocalDateTime date, int score, long ownerId, int answerCount, String ownerName, String title, String tags, LinkedList<Answer> answers){
        super(score, id, ownerId, date, ownerName);
        this.answerCount = answerCount;
        this.title = title;
        this.tags = tags;
        this.answers = answers;
    }

    public int getAnswerCount(){
        return this.answerCount;
    }

    public String getTitle(){
        return this.title;
    }

    //TODO array de strings
    public String getTags(){
        return this.tags;
    }

    //TODO
    public LinkedList<Answer> getAnswers(){
        return this.answers;
    }

    @Override
    public String toString(){
        return "Question{" +
                "answerCount=" + answerCount +
                ", title='" + title + '\'' +
                ", tags='" + tags + '\'' +
                ", answers=" + answers +
                '}';
    }

}
