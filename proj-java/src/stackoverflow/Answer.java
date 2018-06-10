package stackoverflow;

import java.time.LocalDateTime;

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

    @Override
    public Question searchUserInThread(long id){
        if(this.getOwnerId() == id) return this.parentPtr;
        return this.parentPtr.searchUserInThread(id);
    }

    @Override
    public String toString(){
        return "Answer{" +
                "commentCount=" + commentCount
                + ", parentId=" + parentId
                + "} " + super.toString();
    }
}
