package li3;

import engine.TCD;
import view.View;

public class Main {

    public static void main(String[] args){
        new Controller(new TCD(), new View()).run(args);
    }

}
