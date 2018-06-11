package main.java.engine;

import main.java.engine.calendario.Calendario;
import main.java.engine.collections.SortedLinkedList;

import java.time.LocalDate;
import java.util.*;
import java.util.function.Predicate;

public class Community {

    private final Map<Long,Question> questions;
    private final Map<Long,Answer> answers;
    private final Map<Long,User> users;
    private final Map<String,Long> tags;

    private final Calendario<Question> calendarioQuestions;
    private final Calendario<Answer> calendarioAnswers;

    public Community(){
        this.questions = new HashMap<>();
        this.answers = new HashMap<>();
        this.users = new HashMap<>();
        this.tags = new HashMap<>();
        this.calendarioQuestions = new Calendario<>();
        this.calendarioAnswers = new Calendario<>();
    }

    private void updateUserPosts(long ownerId, Post post){
        User user = this.users.get(ownerId);
        if(user!=null) user.addPost(post);
    }

    private void updateQuestionAnswers(Answer answer){
        long parentId = answer.getParentId();
        Question question = questions.get(parentId);
        if (question != null) question.addAnswer(answer);
    }

    public void addQuestion (Question question){
        questions.put(question.getId(),question);
        calendarioQuestions.addElem(question);
        updateUserPosts(question.getOwnerId(), question);
    }

    public void addAnswer(Answer answer){
        answers.put(answer.getId(),answer);
        calendarioAnswers.addElem(answer);
        updateQuestionAnswers(answer);
        updateUserPosts(answer.getOwnerId(), answer);
    }

    public void addUser(User user){
        users.put(user.getId(), user);
    }

    public void addTag(long id, String tag){
        tags.put(tag, id);
    }

    public Question getQuestion(long id){
        return this.questions.get(id);
    }

    public Answer getAnswer(long id){
        return this.answers.get(id);
    }

    public User getUser(long id){
        return this.users.get(id);
    }

    public long getTagId(String tag){
        Long id = tags.get(tag);
        if(id!=null){
            return id;
        } return -2;
    }

    public long getUserCount(){
        return users.size();
    }

    public long getQuestionCount(){
        return questions.size();
    }

    public long getAnswerCount(){
        return answers.size();
    }

    public List<User> getSortedUserList(Comparator<User> userComparator, int N){
        SortedLinkedList<User> users = new SortedLinkedList<>(userComparator, N);
        users.addAll(this.users.values());
        return users;
    }

    private class SortedQuestions implements Predicate<Question> {

        private final SortedLinkedList<Question> list;

        private SortedQuestions(Comparator<Question> comparator, int max){
            this.list = new SortedLinkedList<>(comparator, max);
        }
        @Override
        public boolean test(Question question){
            this.list.add(question);
            return true;
        }

    }

    public List<Question> getSortedQuestionList(LocalDate from, LocalDate to, Comparator<Question> questionComparator, int N){
        SortedQuestions sortedQuestions = new SortedQuestions(questionComparator, N);
        this.calendarioQuestions.iterate(from, to, sortedQuestions);
        return sortedQuestions.list;
    }

    private class SortedAnswers implements Predicate<Answer> {

        private final SortedLinkedList<Answer> list;

        private SortedAnswers(Comparator<Answer> comparator, int max){
            this.list = new SortedLinkedList<>(comparator, max);
        }

        @Override
        public boolean test(Answer answer){
            this.list.add(answer);
            return true;
        }
    }

    public List<Answer> getSortedAnswerList(LocalDate from, LocalDate to, Comparator<Answer> answerComparator, int N){
        SortedAnswers sortedAnswers = new SortedAnswers(answerComparator, N);
        this.calendarioAnswers.iterate(from, to, sortedAnswers);
        return sortedAnswers.list;
    }

    private class FilteredQuestions implements Predicate<Question> {
        private final ArrayList<Question> list;
        private final Predicate<Question> f;
        private int max;

        private FilteredQuestions(Predicate<Question> f, int max){
            this.list = new ArrayList<>(this.max);
            this.f = f;
            this.max = max;
        }
        @Override
        public boolean test(Question question){
            if(this.list.size() >= max) return false;
            if(this.f.test(question)) this.list.add(question);
            return true;
        }
    }

    public List<Question> getFilteredQuestions(LocalDate from, LocalDate to, int N, Predicate<Question> f){
        FilteredQuestions filteredQuestions = new FilteredQuestions(f, N);
        this.calendarioQuestions.iterate(from, to, filteredQuestions);
        return filteredQuestions.list;
    }

    public long countQuestions(LocalDate from, LocalDate to){
        return this.calendarioQuestions.countElements(from, to);
    }

    public long countAnswers(LocalDate from, LocalDate to){
        return this.calendarioAnswers.countElements(from, to);
    }
}
