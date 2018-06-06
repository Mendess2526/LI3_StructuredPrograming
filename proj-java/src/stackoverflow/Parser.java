package stackoverflow;

import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;
import stackoverflow.saxhandlers.PostHandler;
import stackoverflow.saxhandlers.TagsHandler;
import stackoverflow.saxhandlers.UserHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;

public class Parser {
    public static void parse(Community com, String path){
        SAXParserFactory spf = SAXParserFactory.newInstance();
        spf.setNamespaceAware(true);
        try{
            SAXParser saxParser = spf.newSAXParser();
            XMLReader xmlReader = saxParser.getXMLReader();
            xmlReader.setContentHandler(new UserHandler(com));
            xmlReader.parse(convertToFileURL(path + "Users.xml"));
            xmlReader.setContentHandler(new PostHandler(com));
            xmlReader.parse(convertToFileURL(path + "Posts.xml"));
            xmlReader.setContentHandler(new TagsHandler(com));
            xmlReader.parse(convertToFileURL(path + "Tags.xml"));
        }catch(ParserConfigurationException | SAXException | IOException e){
            e.printStackTrace();
        }
    }

    private static String convertToFileURL(String filename) {
        String path = new File(filename).getAbsolutePath();
        if (File.separatorChar != '/') {
            path = path.replace(File.separatorChar, '/');
        }

        if (!path.startsWith("/")) {
            path = "/" + path;
        }
        return "file:" + path;
    }
}
