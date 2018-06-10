package main.java.engine;

import main.java.engine.collections.SortedLinkedList;

import java.util.ArrayList;

public class User {

    private int reputation;
    private long id;
    private String name;
    private String bio;
    private SortedLinkedList<Post> posts;

    public User(int reputation, long id, String name, String bio){
        this.reputation = reputation;
        this.id = id;
        this.name = name;
        this.bio = bio;
        this.posts = new SortedLinkedList<>(new PostDateComparator().reversed());
    }

    public int getReputation(){
        return this.reputation;
    }

    public int getNrPosts(){
        return this.posts.size();
    }

    public long getId(){
        return this.id;
    }

    public String getName(){
        return this.name;
    }

    public String getBio(){
        return this.bio;
    }

    public ArrayList<Post> getPosts(){
        return new ArrayList<>(this.posts);
    }

    public void addPost(Post post){
        posts.addLast(post);
    }

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