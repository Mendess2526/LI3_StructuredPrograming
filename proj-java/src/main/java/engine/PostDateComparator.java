package main.java.engine;

import java.util.Comparator;

public class PostDateComparator implements Comparator<Post> {

    public int compare(Post post1, Post post2){
        return post1.getDate().compareTo(post2.getDate()); }
}
