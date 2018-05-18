package stackoverflow;

import java.time.LocalDateTime;
import java.util.Comparator;

public class Answer extends Post{
    private int commentCount;
    private long parentId;
    private Question parentPtr;

    public Answer(int score, int commentCount, long id, long parentId, long ownerId, LocalDateTime date, String ownerName){
        super(score, id, ownerId, date, ownerName);
        this.commentCount = commentCount;
        this.parentId = parentId;
        this.parentPtr = null;
    }

    public int getCommentCount(){
        return this.commentCount;
    }

    public long getParentId(){
        return this.parentId;
    }

    public Question getParentPtr(){
        return this.parentPtr;
    }

    public void setParentPtr(Question question){
        this.parentPtr = question;
    }

}
