package stackoverflow;

import java.util.Comparator;

public class UserPostCountComparator implements Comparator<User>{

    @Override
    public int compare(User user1, User user2){
        return Integer.compare(user1.getNrPosts(),user2.getNrPosts());
    }
}
