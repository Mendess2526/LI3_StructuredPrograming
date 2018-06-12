package engine;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.*;

/**
 * Classe que define uma questão.
 */
public class Question extends Post {

    /** Número de respostas da questão. */
    private final int answerCount;
    /** Título da questão. */
    private final String title;
    /** Tags da questão. */
    private final String tags;
    /** Lista das respostas da questão. */
    private final LinkedList<Answer> answers;
    /** TODO */
    private LocalDate cachedFrom;
    /** TODO */
    private LocalDate cachedTo;
    /** TODO */
    private int answerCountBetweenDates;

    /**
     * Cria uma questão.
     *
     * @param id          O id da questão.
     * @param date        A data da questão.
     * @param score       O score da questão.
     * @param ownerId     O id do autor da questão.
     * @param answerCount O número de respostas da questão.
     * @param ownerName   O nome do autor da questão.
     * @param title       O título da questão.
     * @param tags        As tags da questão.
     */
    public Question(long id, LocalDateTime date, int score, long ownerId, int answerCount, String ownerName,
                    String title, String tags){
        super(score, id, ownerId, date, ownerName);
        this.answerCount = answerCount;
        this.title = title;
        this.tags = tags;
        this.answers = new LinkedList<>();
    }

    /**
     * Retorna o número de respostas da questão.
     *
     * @return O número de respostas da questão.
     */
    public int getAnswerCount(){
        return this.answerCount;
    }

    /**
     * Retorna o título da questão.
     *
     * @return O título da questão.
     */
    public String getTitle(){
        return this.title;
    }

    /**
     * Retorna as tags da questão.
     *
     * @return As tags da questão.
     */
    public String[] getTags(){
        String[] tags = new String[5];
        StringTokenizer st = new StringTokenizer(this.tags.substring(1), "><");
        int i = 0;
        while(st.hasMoreTokens()){
            String s = st.nextToken();
            tags[i++] = s;
        }
        return tags;
    }

    /**
     * Retorna a lista de respostas da questão.
     *
     * @return A lista de respostas da questão.
     */
    public List<Answer> getAnswers(){
        return new ArrayList<>(this.answers);
    }

    /**
     * Adiciona uma resposta à lista de respostas.
     *
     * @param answer A resposta a adicionar.
     */
    void addAnswer(Answer answer){
        answer.setParentPtr(this);
        answers.addFirst(answer);
    }

    /**
     * Verifica se uma questão tem uma tag.
     *
     * @param tag Uma tag.
     * @return {@code true} se a questão tem a tag, {@code false} caso contrário.
     */
    public boolean hasTag(String tag){
        return this.tags.contains(tag);
    }

    /**
     * Retorna o número de respostas dentro de um intervalo de tempo.
     *
     * @param from A data de início.
     * @param to   A data do fim.
     * @return O número de respostas dentro de um intervalo de tempo.
     */
    public int getAnswerCountBetweenDate(LocalDate from, LocalDate to){
        if(from.equals(this.cachedFrom) && to.equals(this.cachedTo))
            return this.answerCountBetweenDates;
        this.cachedFrom = from;
        this.cachedTo = to;
        int count = 0;
        for(Answer a : this.answers){
            if(a.getDate().isAfter(from.atStartOfDay())
               && a.getDate().isBefore(to.atTime(LocalTime.MAX)))
                count++;
        }
        return (this.answerCountBetweenDates = count);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String toString(){
        return "Question{" +
               "answerCount=" + answerCount +
               ", title='" + title + '\'' +
               ", tags='" + tags + '\'' +
               ", answers=" + answers +
               '}';
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Question searchUserInThread(long id){
        if(this.getOwnerId() == id) return this;
        for(Answer a : this.answers) if(a.getOwnerId() == id) return this;
        return null;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        Question question = (Question) o;
        return answerCount == question.answerCount &&
               Objects.equals(title, question.title) &&
               Objects.equals(tags, question.tags) &&
               Objects.equals(answers, question.answers);
    }

}
