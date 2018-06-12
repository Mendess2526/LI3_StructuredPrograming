package engine;

import java.time.LocalDateTime;
import java.util.Objects;

/**
 * Classe que define uma resposta.
 */
public class Answer extends Post {

    /** Número de comentários da resposta. */
    private final int commentCount;
    /** Id da questão ao qual foi dada a resposta. */
    private final long parentId;
    /** Questão ao qual foi dada a resposta. */
    private Question parentPtr;

    /**
     * Cria uma resposta.
     *
     * @param score        O score da resposta.
     * @param commentCount O número de comentários da resposta.
     * @param id           O id da resposta.
     * @param parentId     O id da questão à qual foi dada a resposta.
     * @param ownerId      O id do autor resposta.
     * @param date         A data da resposta.
     * @param ownerName    O nome do autor da resposta.
     */
    public Answer(int score, int commentCount, long id, long parentId, long ownerId, LocalDateTime date,
                  String ownerName){
        super(score, id, ownerId, date, ownerName);
        this.commentCount = commentCount;
        this.parentId = parentId;
        this.parentPtr = null;
    }

    /**
     * Retorna o número de comentários da resposta.
     *
     * @return O número de comentários da resposta.
     */
    int getCommentCount(){
        return this.commentCount;
    }

    /**
     * Retorna o id do autor da resposta.
     *
     * @return O id do autor da resposta.
     */
    long getParentId(){
        return this.parentId;
    }

    /**
     * Retorna a questão à qual foi dada a resposta.
     *
     * @return A questão à qual foi dada a resposta.
     */
    Question getParentPtr(){
        return this.parentPtr;
    }

    /**
     * Muda a questão à qual foi dada a resposta.
     *
     * @param question Uma questão.
     */
    void setParentPtr(Question question){
        this.parentPtr = question;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    Question searchUserInThread(long id){
        if(this.getOwnerId() == id) return this.parentPtr;
        return this.parentPtr.searchUserInThread(id);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String toString(){
        return "Answer{" +
               "commentCount=" + commentCount
               + ", parentId=" + parentId
               + "} " + super.toString();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        if(!super.equals(o)) return false;
        Answer answer = (Answer) o;
        return commentCount == answer.commentCount &&
               parentId == answer.parentId &&
               Objects.equals(parentPtr, answer.parentPtr);
    }
}