package engine;

import engine.calendario.Chronological;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

public abstract class Post implements Chronological {

    private final long id;
    private final LocalDateTime date;
    private final int score;
    private final long ownerId;
    private final String ownerName;


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

    public boolean isBetweenDates(LocalDate from, LocalDate to){
        return this.date.isAfter(from.atStartOfDay()) && this.date.isBefore(to.atTime(LocalTime.MAX));
    }

}
