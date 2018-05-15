package stackoverflow;

import java.time.LocalDateTime;
import java.util.LinkedList;

public class Question{
    private long id;
    private LocalDateTime date;
    private int score;
    private long ownerId;
    private int answerCount;
    private String ownerName;
    private String title;
    private String tags;
    private LinkedList<Answer> answers;

    public Question(long id, LocalDateTime date, int score, long ownerId, int answerCount, String ownerName, String title, String tags, LinkedList<Answer> answers){
        this.id = id;
        this.date = date;
        this.score = score;
        this.ownerId = ownerId;
        this.answerCount = answerCount;
        this.ownerName = ownerName;
        this.title = title;
        this.tags = tags;
        this.answers = answers;
    }

    public long getId(){
        return this.id;
    }

    public LocalDateTime getDate(){
        return this.date;
    }

    public int getScore(){
        return this.score;
    }

    public long getOwnerId(){
        return this.ownerId;
    }

    public int getAnswerCount(){
        return this.answerCount;
    }

    public String getOwnerName(){
        return this.ownerName;
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
                "id=" + id +
                ", date=" + date +
                ", score=" + score +
                ", ownerId=" + ownerId +
                ", answerCount=" + answerCount +
                ", ownerName='" + ownerName + '\'' +
                ", title='" + title + '\'' +
                ", tags='" + tags + '\'' +
                ", answers=" + answers +
                '}';
    }

}
