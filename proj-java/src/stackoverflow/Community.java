package stackoverflow;

import stackoverflow.calendario.Calendario;
import stackoverflow.calendario.CalendarioPredicate;
import stackoverflow.calendario.Chronological;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@SuppressWarnings("WeakerAccess")
public class Community {

    private Map<Long,Question> questions;
    private Map<Long,Answer> answers;
    private Map<Long,User> users;
    private Map<String,Long> tags;

    private Calendario<Question> calendarioQuestions;
    private Calendario<Answer> calendarioAnswers;

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
        SortedLinkedList<User> users = new SortedLinkedList<>();
        for(User user : this.users.values()){
            users.addFirst(user, userComparator, N);
        }
        return users;
    }

    private class SortedQuestions implements CalendarioPredicate<Question> {

        private SortedLinkedList<Question> list;
        private Comparator<Question> comparator;
        private int max;

        SortedQuestions(Comparator<Question> comparator, int max){
            this.comparator = comparator;
            this.max = max;
            this.list = new SortedLinkedList<>();
        }
        @Override
        public boolean test(Question question){
            this.list.addFirst(question, this.comparator, this.max);
            return true;
        }
    }

    public List<Question> getSortedQuestionList(LocalDate from, LocalDate to, Comparator<Question> questionComparator, int N){
        SortedQuestions sortedQuestions = new SortedQuestions(questionComparator, N);
        this.calendarioQuestions.iterate(from, to, sortedQuestions);
        return sortedQuestions.list;
    }
    //TODO

    public List<Question> getSortedQuestionListWithData(LocalDateTime from, LocalDateTime to){
        return null;
    }

    public List<Answer> getSortedAnswerList(LocalDateTime from, LocalDateTime to, Comparator<User> userComparatorint, int N){
        return null;
    }

    public long getTagId(String tag){
        Long id = tags.get(tag);
        if(id!=null){
            return id;
        } return -2;
    }
}
