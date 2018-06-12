package engine;

import java.util.Comparator;

/**
 * Comparador da reputação dos users.
 */
class UserReputationComparator implements Comparator<User> {

    /**
     * {@inheritDoc}
     */
    @Override
    public int compare(User user1, User user2){
        return Integer.compare(user1.getReputation(),user2.getReputation());
    }
}
