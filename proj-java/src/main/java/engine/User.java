package engine;


import engine.collections.SortedLinkedList;
import engine.comparators.PostDateComparator;

import java.util.ArrayList;

/**
 * Classe que define um user.
 */
public class User {

    /** Reputação do user. */
    private final int reputation;
    /** Id do user. */
    private final long id;
    /** Nome do user. */
    private final String name;
    /** Biografia do user. */
    private final String bio;
    /** Lista de posts do user. */
    private final SortedLinkedList<Post> posts;

    /**
     * Cria um user.
     *
     * @param reputation A reputação do user.
     * @param id         O id do user.
     * @param name       O nome do user.
     * @param bio        A biografia do user.
     */
    public User(int reputation, long id, String name, String bio){
        this.reputation = reputation;
        this.id = id;
        this.name = name;
        this.bio = bio;
        this.posts = new SortedLinkedList<>(new PostDateComparator().reversed());
    }

    /**
     * Retorna a reputação do user.
     *
     * @return A reputação do user.
     */
    public int getReputation(){
        return this.reputation;
    }

    /**
     * Retorna o número de posts do user.
     *
     * @return O número de posts do user.
     */
    public int getNrPosts(){
        return this.posts.size();
    }

    /**
     * Retorna o id do user.
     *
     * @return O id do user.
     */
    public long getId(){
        return this.id;
    }

    /**
     * Retorna o nome do user.
     *
     * @return O nome do user.
     */
    public String getName(){
        return this.name;
    }

    /**
     * Retorna a biografia do user.
     *
     * @return A biografia do user.
     */
    public String getBio(){
        return this.bio;
    }

    /**
     * Retorna a lista de posts do user.
     *
     * @return A lista de posts do user.
     */
    public ArrayList<Post> getPosts(){
        return new ArrayList<>(this.posts);
    }

    /**
     * Adiciona um post à lista de posts.
     *
     * @param post Post a adicionar.
     */
    public void addPost(Post post){
        posts.addLast(post);
    }


    /**
     * {@inheritDoc}
     */
    @Override
    public String toString(){
        return "User{" +
               "reputation=" + reputation
               + ", id=" + id
               + ", name='" + name + '\''
               + ", bio='" + bio + '\''
               + ", posts=" + posts
               + '}';
    }
}
