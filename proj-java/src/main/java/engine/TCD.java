package engine;


import common.Pair;
import engine.comparators.AnswerScoreComparator;
import engine.comparators.QuestionAnswerCountComparator;
import engine.comparators.UserPostCountComparator;
import engine.comparators.UserReputationComparator;
import li3.TADCommunity;

import java.time.LocalDate;
import java.util.*;

import static java.util.Comparator.comparing;
import static java.util.Comparator.reverseOrder;

public class TCD implements TADCommunity {

    private final Community com;

    public TCD(){
        this.com = new Community();
    }

    private List<Long> idsFromPosts(Collection<? extends Post> posts, int N){
        List<Long> ids;
        if(N < 1)
            ids = new ArrayList<>((N = posts.size()));
        else
            ids = new ArrayList<>(N);
        int i = 0;
        for(Iterator<? extends Post> it = posts.iterator(); i++ < N && it.hasNext(); ){
            ids.add(it.next().getId());
        }
        return ids;
    }

    @Override
    public void load(String dumpPath){
        Parser.parse(this.com, dumpPath);
    }

    @Override
    public Pair<String,String> infoFromPost(long id){
        Question question = this.com.getQuestion(id);
        if(question == null){
            Answer answer = this.com.getAnswer(id);
            if(answer == null) return null;
            question = answer.getParentPtr();
            if(question == null) return null;
        }
        String name = question.getOwnerName();
        if(name == null){
            name = this.com.getUser(question.getOwnerId()).getName();
        }
        return new Pair<>(question.getTitle(), name);
    }

    @Override
    public List<Long> topMostActive(int N){
        List<User> users = this.com.getSortedUserList(new UserPostCountComparator().reversed(), N);
        List<Long> ids = new ArrayList<>(N);
        for(int i = 0; i < N && i < users.size(); i++)
            ids.add(users.get(i).getId());
        return ids;
    }

    @Override
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        return new Pair<>(this.com.countQuestions(begin, end), this.com.countAnswers(begin, end));
    }

    @Override
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        List<Question> questions = this.com.getFilteredQuestions(
                end, begin, Integer.MAX_VALUE, f -> f.hasTag(tag));
        return idsFromPosts(questions, -1);
    }

    @Override
    public Pair<String,List<Long>> getUserInfo(long id){
        User user = this.com.getUser(id);
        if(user == null) return null;
        String bio = user.getBio();
        List<Long> ids = new ArrayList<>(10);
        for(Post p : user.getPosts()){
            ids.add(p.getId());
            if(ids.size() == 10) break;
        }
        return new Pair<>(bio, ids);
    }

    @Override
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
        List<Answer> answers = this.com.getSortedAnswerList(
                begin, end, new AnswerScoreComparator().reversed(), N);
        return idsFromPosts(answers, N);
    }

    @Override
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
        List<Question> questions = this.com.getSortedQuestionList(
                begin,
                end,
                new QuestionAnswerCountComparator(begin, end),
                N);
        return idsFromPosts(questions, N);
    }

    @Override
    public List<Long> containsWord(int N, String word){
        List<Question> questions = this.com.getFilteredQuestions(
                LocalDate.MAX, LocalDate.MIN, N, q -> q.getTitle().contains(word));
        return idsFromPosts(questions, N);
    }

    @Override
    public List<Long> bothParticipated(int N, long id1, long id2){
        User user1 = this.com.getUser(id1);
        User user2 = this.com.getUser(id2);
        if(user1 == null || user2 == null) return new ArrayList<>();
        List<Post> posts;
        long searchId;
        if(user1.getNrPosts() < user2.getNrPosts()){
            posts = user1.getPosts();
            searchId = id2;
        }else{
            posts = user2.getPosts();
            searchId = id1;
        }
        List<Question> questions = new ArrayList<>(N);
        Set<Long> ids = new HashSet<>(N);
        for(Post p : posts){
            Question q = p.searchUserInThread(searchId);
            if(q != null && !ids.contains(q.getId())){
                questions.add(q);
                ids.add(q.getId());
            }
        }
        return idsFromPosts(questions, N);
    }

    @Override
    public long betterAnswer(long id){
        Question question = this.com.getQuestion(id);
        if(question == null) return 0;
        double bestP = 0;
        long idBest = -1;
        for(Answer a : question.getAnswers()){
            int rep = this.com.getUser(a.getOwnerId()).getReputation();
            long idAnswer = a.getId();
            double testScore = (a.getScore() * 0.65) + (rep * 0.25) + (a.getCommentCount() * 0.1);
            if(testScore > bestP){
                bestP = testScore;
                idBest = idAnswer;
            }
        }
        return idBest;
    }

    @Override
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        List<User> users = this.com.getSortedUserList(new UserReputationComparator().reversed(), N);
        Map<String,Long> counts = new HashMap<>();
        int i = 0;
        for(Iterator<User> iterator = users.iterator(); i++ < N && iterator.hasNext(); ){
            User u = iterator.next();
            for(Post p : u.getPosts())
                if(p instanceof Question && p.isBetweenDates(begin, end))
                    for(String s : ((Question) p).getTags())
                        if(s != null) counts.merge(s, 1L, Long::sum);
        }
        Queue<Pair<String,Long>> top = new PriorityQueue<>(N, comparing(Pair::getSnd, reverseOrder()));
        counts.forEach((key, value) -> top.add(new Pair<>(key, value)));
        N = N < top.size() ? N : top.size();
        List<Long> ids = new ArrayList<>(N);
        for(i = 0; i < N; i++)
            ids.add(this.com.getTagId(top.poll().getFst()));
        return ids;
    }

    @Override
    public void clear(){

    }

    public long getUserCount(){
        return this.com.getUserCount();
    }

    public long getQuestionCount(){
        return this.com.getQuestionCount();
    }

    public long getAnswerCount(){
        return this.com.getAnswerCount();
    }
}
