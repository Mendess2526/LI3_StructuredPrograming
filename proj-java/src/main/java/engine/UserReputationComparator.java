package engine;

import java.util.Comparator;

class UserReputationComparator implements Comparator<User> {

    @Override
    public int compare(User user1, User user2){
        return Integer.compare(user1.getReputation(),user2.getReputation());
    }
}
