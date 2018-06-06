package stackoverflow;

import stackoverflow.calendario.Chronological;

import java.time.LocalDateTime;

public abstract class Post extends Chronological {

    private long id;
    private LocalDateTime date;
    private int score;
    private long ownerId;
    private String ownerName;


    Post(int score, long id, long ownerId, LocalDateTime date, String ownerName){
        this.id = id;
        this.score = score;
        this.ownerId = ownerId;
        this.date = date;
        this.ownerName = ownerName;
    }

    public long getId(){
        return this.id;
    }

    @Override
    public LocalDateTime getDate(){
        return this.date;
    }

    public int getScore(){
        return this.score;
    }

    public long getOwnerId(){
        return this.ownerId;
    }

    public String getOwnerName(){
        return this.ownerName;
    }

    @Override
    public String toString(){
        return "Post{" +
                "id=" + id +
                ", date=" + date +
                ", score=" + score +
                ", ownerId=" + ownerId +
                ", ownerName='" + ownerName + '\'' +
                '}';
    }

    public abstract Question searchUserInThread(long id);
}
