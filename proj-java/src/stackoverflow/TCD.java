package stackoverflow;

<<<<<<< HEAD
import main.java.common.Pair;
import main.java.li3.TADCommunity;

import java.time.LocalDate;
import java.util.List;

public class TCD implements TADCommunity{
    @Override
    public void load(String dumpPath){

    }

    @Override
    public Pair<String, String> infoFromPost(long id){
        return null;
    }

    @Override
    public List<Long> topMostActive(int N){
        return null;
    }

    @Override
    public Pair<Long, Long> totalPosts(LocalDate begin, LocalDate end){
        return null;
    }

    @Override
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        return null;
    }

    @Override
    public Pair<String, List<Long>> getUserInfo(long id){
        return null;
    }

    @Override
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
        return null;
    }

    @Override
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
        return null;
    }

    @Override
    public List<Long> containsWord(int N, String word){
        return null;
    }

    @Override
    public List<Long> bothParticipated(int N, long id1, long id2){
        return null;
    }

    @Override
    public long betterAnswer(long id){
        return 0;
    }

    @Override
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        return null;
    }

    @Override
    public void clear(){

    }
=======
public class TCD implements TCDComm{
>>>>>>> d33a0d213ef88e0e9d6af6e593957feeb940b153
}
