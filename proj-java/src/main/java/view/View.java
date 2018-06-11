package view;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import static java.util.Arrays.asList;

public class View {

    private Menu mainMenu;
    private Menu pickQueryMenu;

    public int runMainMenu(){
        if(this.mainMenu == null) makeMainMenu();
        this.mainMenu.execute();
        return this.mainMenu.getResult();
    }

    public int runPickQueryMenu(){
        if(this.pickQueryMenu == null) makePickQueryMenu();
        this.pickQueryMenu.execute();
        return this.pickQueryMenu.getResult();
    }

    public void showResults(int queryNum, Object result, long time){
        System.out.println("Query " + queryNum + ":");
        System.out.println(result);
        System.out.println("Time taken: " + time);
    }

    public String requestDumpPath(){
        return new Form("Insert dump path", Collections.singletonList("Dump path: "))
                .execute()
                .getResult()
                .get(0);
    }

    public void notifyLoading(){
        System.out.println("Loading from xml...");
    }

    private void makeMainMenu(){
        this.mainMenu = new Menu("Main", asList("Run all queries", "Pick one query"));
    }

    private void makePickQueryMenu(){
        List<String> options = new ArrayList<>();
        for(int i = 1; i < 12; i++) options.add("Query " + i);
        this.pickQueryMenu = new Menu("Pick a Query", options);
    }
}
