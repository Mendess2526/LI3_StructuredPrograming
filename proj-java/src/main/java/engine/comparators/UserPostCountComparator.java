package engine.comparators;

import engine.User;

import java.util.Comparator;

/**
 * Comparador do número de posts dos users.
 */
public class UserPostCountComparator implements Comparator<User> {

    /**
     * {@inheritDoc}
     */
    @Override
    public int compare(User user1, User user2){
        return Integer.compare(user1.getNrPosts(), user2.getNrPosts());
    }
}
