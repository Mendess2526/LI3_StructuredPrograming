package engine;


import engine.collections.SortedLinkedList;

import java.time.LocalDate;
import java.util.*;
import java.util.function.Predicate;

/**
 * Classe que organiza as entidades.
 */
public class Community {

    /** Map de questões. */
    private final Map<Long,Question> questions;
    /** Map de respostas. */
    private final Map<Long,Answer> answers;
    /** Map de users. */
    private final Map<Long,User> users;
    /** Map de tags. */
    private final Map<String,Long> tags;

    /** Calendário de questões. */
    private final Calendario<Question> calendarioQuestions;
    /** Calendário de respostas. */
    private final Calendario<Answer> calendarioAnswers;

    /**
     * Cria uma instância da estrutura.
     */
    Community(){
        this.questions = new HashMap<>();
        this.answers = new HashMap<>();
        this.users = new HashMap<>();
        this.tags = new HashMap<>();
        this.calendarioQuestions = new Calendario<>();
        this.calendarioAnswers = new Calendario<>();
    }

    /**
     * Adiciona um post à lista de posts de um user.
     *
     * @param ownerId O id do user a quem vais adicionar.
     * @param post    Um post.
     */
    private void updateUserPosts(long ownerId, Post post){
        User user = this.users.get(ownerId);
        if(user != null) user.addPost(post);
    }

    /**
     * Adiciona uma resposta à lista de respostas de uma questão.
     *
     * @param answer Uma resposta.
     */
    private void updateQuestionAnswers(Answer answer){
        long parentId = answer.getParentId();
        Question question = questions.get(parentId);
        if(question != null) question.addAnswer(answer);
    }

    /**
     * Adiciona uma questão à estrutura.
     *
     * @param question A questão a adicionar.
     */
    public void addQuestion(Question question){
        questions.put(question.getId(), question);
        calendarioQuestions.addElem(question);
        updateUserPosts(question.getOwnerId(), question);
    }

    /**
     * Adiciona uma resposta à estrutura.
     *
     * @param answer A resposta a adicionar.
     */
    public void addAnswer(Answer answer){
        answers.put(answer.getId(), answer);
        calendarioAnswers.addElem(answer);
        updateQuestionAnswers(answer);
        updateUserPosts(answer.getOwnerId(), answer);
    }

    /**
     * Adiciona um user à estrutura.
     *
     * @param user O user a adicionar.
     */
    public void addUser(User user){
        users.put(user.getId(), user);
    }

    /**
     * Adiciona uma tag à estrutura.
     *
     * @param id  O id da tag.
     * @param tag O nome da tag
     */
    public void addTag(long id, String tag){
        tags.put(tag, id);
    }

    /**
     * Retorna uma questão.
     *
     * @param id O id da questão que queremos.
     * @return Uma questão.
     */
    Question getQuestion(long id){
        return this.questions.get(id);
    }

    /**
     * Retorna uma resposta.
     *
     * @param id O id da resposta que queremos.
     * @return Uma resposta.
     */
    Answer getAnswer(long id){
        return this.answers.get(id);
    }

    /**
     * Retorna um user.
     *
     * @param id O id do user que queremos.
     * @return Um user.
     */
    User getUser(long id){
        return this.users.get(id);
    }


    /**
     * Retorna o id de uma tag.
     *
     * @param tag A tag que queremos.
     * @return Um id.
     */
    long getTagId(String tag){
        Long id = tags.get(tag);
        if(id != null){
            return id;
        }
        return -2;
    }

    /**
     * Retorna o número de users.
     *
     * @return O número de users.
     */
    long getUserCount(){
        return users.size();
    }

    /**
     * Retorna o número de questões.
     *
     * @return O número de questões.
     */
    long getQuestionCount(){
        return questions.size();
    }

    /**
     * Retorna o número de respostas.
     *
     * @return O número de respostas.
     */
    long getAnswerCount(){
        return answers.size();
    }

    /**
     * Retorna uma lista ordenada de users.
     *
     * @param userComparator Um comparador de users.
     * @param N              O tamanho da lista.
     * @return Uma lista ordenada de users.
     */
    List<User> getSortedUserList(Comparator<User> userComparator, int N){
        SortedLinkedList<User> users = new SortedLinkedList<>(userComparator, N);
        users.addAll(this.users.values());
        return users;
    }

    /**
     * Retorna uma lista ordenada de questões dentro de um intervalo de tempo.
     *
     * @param from               A data de início.
     * @param to                 A data do fim.
     * @param qComparator Um comparador de questões.
     * @param N                  O tamanho da lista.
     * @return Uma lista ordenada de questões.
     */
    List<Question> getSortedQuestionList(LocalDate from, LocalDate to, Comparator<Question> qComparator, int N){
        SortedQuestions sortedQuestions = new SortedQuestions(qComparator, N);
        this.calendarioQuestions.iterate(from, to, sortedQuestions);
        List<Question> list = new ArrayList<>();
        for(int i = 0; i < N && !sortedQuestions.list.isEmpty(); i++)
            list.add(sortedQuestions.list.poll());
        return list;
    }

    /**
     * Retorna uma lista ordenada de respostas dentro de um intervalo de tempo.
     *
     * @param from             A data de início.
     * @param to               A data do fim.
     * @param aComparator Um comparador de respostas.
     * @param N                O tamanho da lista.
     * @return Uma lista ordenada de respostas.
     */
    List<Answer> getSortedAnswerList(LocalDate from, LocalDate to, Comparator<Answer> aComparator, int N){
        SortedAnswers sortedAnswers = new SortedAnswers(aComparator, N);
        this.calendarioAnswers.iterate(from, to, sortedAnswers);
        List<Answer> list = new ArrayList<>();
        for(int i = 0; i < N && !sortedAnswers.list.isEmpty(); i++)
            list.add(sortedAnswers.list.poll());
        return list;
    }

    /**
     * Retorna uma lista de questões filtrada dentro de um intervalo de tempo.
     *
     * @param from A data de início.
     * @param to   A data do fim.
     * @param N    O tamanho da lista.
     * @param f    Função a aplicar a todos os elementos.
     * @return Uma lista de questões filtrada.
     */
    List<Question> getFilteredQuestions(LocalDate from, LocalDate to, int N, Predicate<Question> f){
        FilteredQuestions filteredQuestions = new FilteredQuestions(f, N);
        this.calendarioQuestions.iterate(from, to, filteredQuestions);
        return filteredQuestions.list;
    }

    /**
     * Conta as questões dentro de um intervalo de tempo.
     *
     * @param from A data de início.
     * @param to   A data do fim.
     * @return O número de questões.
     */
    long countQuestions(LocalDate from, LocalDate to){
        return this.calendarioQuestions.countElements(from, to);
    }

    /**
     * Conta as respostas dentro de um intervalo de tempo.
     *
     * @param from A data de início.
     * @param to   A data do fim.
     * @return O número de respostas.
     */
    long countAnswers(LocalDate from, LocalDate to){
        return this.calendarioAnswers.countElements(from, to);
    }

    /**
     * Implementação do predicado para obter questões ordenadas.
     */
    private class SortedQuestions implements Predicate<Question> {

        private final PriorityQueue<Question> list;

        private SortedQuestions(Comparator<Question> comparator, int max){
            this.list = new PriorityQueue<>(max, comparator);
        }

        /**
         * {@inheritDoc}
         */
        @Override
        public boolean test(Question question){
            this.list.add(question);
            return true;
        }

    }

    /**
     * Implementação do predicado para obter respostas ordenadas.
     */
    private class SortedAnswers implements Predicate<Answer> {

        private final PriorityQueue<Answer> list;

        private SortedAnswers(Comparator<Answer> comparator, int max){
            this.list = new PriorityQueue<>(max, comparator);
        }

        /**
         * {@inheritDoc}
         */
        @Override
        public boolean test(Answer answer){
            this.list.add(answer);
            return true;
        }
    }

    /**
     * Implementação do predicado para obter questões filtradas.
     */
    private class FilteredQuestions implements Predicate<Question> {

        private final List<Question> list;
        private final Predicate<Question> f;
        private int max;

        private FilteredQuestions(Predicate<Question> f, int max){
            this.list = new ArrayList<>(this.max);
            this.f = f;
            this.max = max;
        }

        /**
         * {@inheritDoc}
         */
        @Override
        public boolean test(Question question){
            if(this.list.size() >= max) return false;
            if(this.f.test(question)) this.list.add(question);
            return true;
        }
    }
}
