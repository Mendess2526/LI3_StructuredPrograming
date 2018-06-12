package engine;

import engine.calendario.Chronological;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;

/**
 * Classe que define um post.
 */
public abstract class Post implements Chronological {

    /** O id do post. */
    private final long id;
    /** A data do post. */
    private final LocalDateTime date;
    /** O score do post. */
    private final int score;
    /** O id do autor do post. */
    private final long ownerId;
    /** O nome do autor do post. */
    private final String ownerName;

    /**
     * Cria um post.
     * @param score O score do post.
     * @param id O id do post.
     * @param ownerId O id do autor do post.
     * @param date A data do post.
     * @param ownerName O nome do autor do post.
     */
    Post(int score, long id, long ownerId, LocalDateTime date, String ownerName){
        this.id = id;
        this.score = score;
        this.ownerId = ownerId;
        this.date = date;
        this.ownerName = ownerName;
    }

    /**
     * Retorna o id do post.
     * @return O id do post.
     */
    public long getId(){
        return this.id;
    }

    /**
     * Retorna a data do post.
     * @return A data do post.
     */
    public LocalDateTime getDate(){
        return this.date;
    }

    /**
     * Retorna o score do post.
     * @return O id do post.
     */
    public int getScore(){
        return this.score;
    }

    /**
     * Retorna o id do autor do post.
     * @return O id do autor do post.
     */
    public long getOwnerId(){
        return this.ownerId;
    }

    /**
     * Retorna o nome do autor do post.
     * @return O nome do autor do post.
     */
    public String getOwnerName(){
        return this.ownerName;
    }


    /**
     * {@inheritDoc}
     */
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

    /**
     * Procura se um user é o autor de algum post na thread.
     * @param id O user à procura.
     * @return A questão da thread seja autor de algum post, null caso contrário.
     */
    public abstract Question searchUserInThread(long id);

    /**
     * Verifica se o post está dentro de um intervalo de tempo.
     * @param from A data de início.
     * @param to A data do fim.
     * @return {@code true} se estiver no intervalo de tempo, {@code false} caso contrário.
     */
    public boolean isBetweenDates(LocalDate from, LocalDate to){
        return this.date.isAfter(from.atStartOfDay()) && this.date.isBefore(to.atTime(LocalTime.MAX));
    }

}
