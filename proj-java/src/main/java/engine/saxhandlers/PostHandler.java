package engine.saxhandlers;

import engine.Answer;
import engine.Community;
import engine.Question;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.time.LocalDateTime;

public class PostHandler extends DefaultHandler {

    /** Instância onde guardar as tags parsed. */
    private final Community com;

    /**
     * Cria o handler de posts.
     *
     * @param com Instância onde guardar os posts parsed.
     */
    public PostHandler(Community com){
        super();
        this.com = com;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException{
        super.startElement(uri, localName, qName, attributes);
        PostType pt = postTypeFromString(attributes.getValue("PostTypeId"));
        if(pt == PostType.NEITHER) return;
        long id = Long.parseLong(attributes.getValue("Id"));
        long ownerId = Long.parseLong(attributes.getValue("OwnerUserId"));
        int score = Integer.parseInt(attributes.getValue("Score"));
        int commentCount = Integer.parseInt(attributes.getValue("CommentCount"));
        LocalDateTime date = LocalDateTime.parse(attributes.getValue("CreationDate"));
        String ownerName = attributes.getValue("OwnerDisplayName");

        switch(pt){
            case QUESTION:
                // Question attr
                String title = attributes.getValue("Title");
                String tags = attributes.getValue("Tags");
                int answerCount = Integer.parseInt(attributes.getValue("AnswerCount"));
                com.addQuestion(new Question(id, date, score, ownerId, answerCount, ownerName, title, tags));
                break;
            case ANSWER:
                // Answer attr
                long parentId = Long.parseLong(attributes.getValue("ParentId"));
                com.addAnswer(new Answer(score, commentCount, id, parentId, ownerId, date, ownerName));
                break;
            default:
                assert false;
                break;
        }
    }

    /**
     * Converte uma string para o tipo de post correspondente.
     * @param s String para converter.
     * @return O tipo de post.
     */
    private PostType postTypeFromString(String s){
        if("1".equals(s)) return PostType.QUESTION;
        if("2".equals(s)) return PostType.ANSWER;
        return PostType.NEITHER;
    }

    /**
     * Define os tipos de post
     */
    private enum PostType {
        /** Questão */
        QUESTION,
        /** Resposta */
        ANSWER,
        /** Nenhum dos anteriores */
        NEITHER
    }
}