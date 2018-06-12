package engine.saxhandlers;

import engine.Community;
import engine.User;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class UserHandler extends DefaultHandler {

    private final Community com;

    public UserHandler(Community com){
        super();
        this.com = com;
    }


    /**
     * {@inheritDoc}
     */
    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException{
        super.startElement(uri, localName, qName, attributes);
        if(!localName.equals("row")) return;
        long userId = Long.parseLong(attributes.getValue("Id"));
        int reputation = Integer.parseInt(attributes.getValue("Reputation"));
        String displayName = attributes.getValue("DisplayName");
        String bio = attributes.getValue("AboutMe");
        this.com.addUser(new User(reputation, userId, displayName, bio));
    }
}
