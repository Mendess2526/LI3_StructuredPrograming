package engine;

import engine.saxhandlers.PostHandler;
import engine.saxhandlers.TagsHandler;
import engine.saxhandlers.UserHandler;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;

/**
 * Classe encarregue de fazer parse dos ficheiros xml.
 */
class Parser {

    private Parser(){
    }

    /**
     * Realiza o parse dos ficheiros xml que se encontram no {@code path}
     *
     * @param com  Instância de {@link Community} onde serão guardados os resultados
     * @param path O caminho para os executáveis.
     */
    static void parse(Community com, String path){
        SAXParserFactory spf = SAXParserFactory.newInstance();
        spf.setNamespaceAware(true);
        try{
            SAXParser saxParser = spf.newSAXParser();
            XMLReader xmlReader = saxParser.getXMLReader();
            xmlReader.setContentHandler(new UserHandler(com));
            xmlReader.parse(convertToFileURL(path + "/Users.xml"));
            xmlReader.setContentHandler(new PostHandler(com));
            xmlReader.parse(convertToFileURL(path + "/Posts.xml"));
            xmlReader.setContentHandler(new TagsHandler(com));
            xmlReader.parse(convertToFileURL(path + "/Tags.xml"));
        }catch(ParserConfigurationException | SAXException | IOException e){
            e.printStackTrace();
        }
    }

    /**
     * Converte o caminho para um {@code FileUrl}.
     * @param filename O caminho para o ficheiro.
     * @return A string convertida.
     */
    private static String convertToFileURL(String filename){
        String path = new File(filename).getAbsolutePath();
        if(File.separatorChar != '/'){
            path = path.replace(File.separatorChar, '/');
        }

        if(!path.startsWith("/")){
            path = "/" + path;
        }
        return "file:" + path;
    }
}
