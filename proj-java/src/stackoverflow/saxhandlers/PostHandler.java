package stackoverflow.saxhandlers;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import stackoverflow.Community;

import java.time.LocalDateTime;

public class PostHandler extends DefaultHandler {

    private Community com;

    public PostHandler(Community com){
        super();
        this.com = com;
    }

    private enum PostType {
        QUESTION,
        ANSWER,
        NEITHER
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException{
        super.startElement(uri, localName, qName, attributes);
        PostType pt = postTypeFromString(attributes.getValue("PostType"));
        if(pt == PostType.NEITHER) return;
        long id = Long.parseLong(attributes.getValue("Id"));
        long ownerId = Long.parseLong(attributes.getValue("OwnerUserId"));
        int score = Integer.parseInt(attributes.getValue("Score"));
        int commentCount = Integer.parseInt(attributes.getValue("CommentCount"));
        LocalDateTime date = LocalDateTime.parse(attributes.getValue("CreationDate"));
        String ownerName = attributes.getValue("OwnerDisplayName");

        assert id != -2;
        assert ownerId != -2;
        assert score != Integer.MIN_VALUE;
        assert date != null;
        assert commentCount != -1;
        //if(ownerName != null) System.out.print("Owner name: " + ownerName + "\t");

        switch(pt){
            case QUESTION:
                // Question attr
                String title = attributes.getValue("Title");
                String tags = attributes.getValue("Tags");
                int answerCount = Integer.parseInt(attributes.getValue("AnswerCount"));

                assert !"".equals(title);
                assert !"".equals(tags);
                break;
            case ANSWER:
                // Answer attr
                long parentId = Long.parseLong(attributes.getValue("ParentId"));
                break;
            default:
                assert false;
                break;
        }
    }

    private PostType postTypeFromString(String s){
        if("1".equals(s)) return PostType.QUESTION;
        if("2".equals(s)) return PostType.ANSWER;
        return PostType.NEITHER;
    }
}