package main.java.engine;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.*;

public class Question extends Post{
    private int answerCount;
    private String title;
    private String tags;
    private LinkedList<Answer> answers;
    private LocalDate cachedFrom;
    private LocalDate cachedTo;
    private int answerCountBetweenDates;

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

    public Question searchUserInThread(long id){
        if(this.getOwnerId() == id) return this;
        for(Answer a: this.answers) if(a.getOwnerId() == id) return this;
        return null;
    }

    public int getAnswerCountBetweenDate(LocalDate from, LocalDate to){
        if(from.equals(this.cachedFrom) && to.equals(this.cachedTo))
            return this.answerCountBetweenDates;
        this.cachedFrom = from;
        this.cachedTo = to;
        int count = 0;
        for(Answer a: this.answers){
            if(a.getDate().isAfter(from.atStartOfDay())
               && a.getDate().isBefore(to.atTime(LocalTime.MAX)))
                count++;
        }
        return (this.answerCountBetweenDates = count);
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
