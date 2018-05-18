package stackoverflow;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Objects;
import java.util.StringTokenizer;

public class Question extends Post{
    private int answerCount;
    private String title;
    private String tags;
    private LinkedList<Answer> answers;

    public Question(long id, LocalDateTime date, int score, long ownerId, int answerCount, String ownerName, String title, String tags){
        super(score, id, ownerId, date, ownerName);
        this.answerCount = answerCount;
        this.title = title;
        this.tags = tags;
        this.answers = new LinkedList<>();
    }

    public int getAnswerCount(){
        return this.answerCount;
    }

    public String getTitle(){
        return this.title;
    }

    public String[] getTags(){
        String[] tags = new String[5];
        StringTokenizer st = new StringTokenizer(this.tags.substring(1), "><");
        int i = 0;
        while (st.hasMoreTokens()){
            String s = st.nextToken();
            tags[i++] = s;
        }
        return tags;
    }

    //TODO
    public LinkedList<Answer> getAnswers(){
        return this.answers;
    }

    public void addAnswer(Answer answer){
        answer.setParentPtr(this);
        answers.addFirst(answer);
    }

    public boolean hasTag(String tag){
        return this.tags.contains(tag);
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

    @Override
    public boolean equals(Object o){
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Question question = (Question) o;
        return answerCount == question.answerCount &&
                Objects.equals(title, question.title) &&
                Objects.equals(tags, question.tags) &&
                Objects.equals(answers, question.answers);
    }

}
