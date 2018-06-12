package view;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

import static java.util.Arrays.asList;

@SuppressWarnings({"WeakerAccess", "SameParameterValue"})
public class View {

    private static final String RESET = "\033[0m";

    static String RED(String s){
        return "\033[31m" + s + RESET;
    }
    static String GREEN(String s){
        return "\033[32m" + s + RESET;
    }
    static String BLUE(String s){
        return "\033[34m" + s + RESET;
    }
    static String PURPLE(String s){
        return "\033[35m" + s + RESET;
    }
    static String YELLOW(String s){
        return "\033[33m" + s + RESET;
    }
    static String BOLD(String s){
        return "\033[1m" + s + RESET;
    }
    static String UNDERLINE(String s){
        return "\033[4m" + s + RESET;
    }

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

    public void showResults(int queryNum, List parameters, Object result, long time){
        System.out.print(BOLD(GREEN("Query " + queryNum + ": ")));
        System.out.println(GREEN(parameters.toString()));
        System.out.println(YELLOW(result.toString()));
        System.out.println(PURPLE("Time taken: " + time));
    }

    public String requestDumpPath(){
        return new Form("Insert dump path", Collections.singletonList("Dump path: "))
                .execute()
                .getResult()
                .get(0);
    }

    public void notifyLoading(){
        System.out.println(BOLD(BLUE("Loading from xml...")));
    }

    public void showEntityCounts(long users, long questions, long answers){
        System.out.println(BOLD("Users:    \t") + users);
        System.out.println(BOLD("Questions:\t") + questions);
        System.out.println(BOLD("Answers:  \t") + answers);
    }

    public void requestContinue(){
        System.out.print("Press ENTER to continue: ");
        new Scanner(System.in).nextLine();
    }

    public List<String> runForm(List<String> fields){
        Form form = new Form("Pick parameters", fields);
        return form.execute().getResult();
    }

    private void makeMainMenu(){
        this.mainMenu = new Menu("Main", asList("Run all queries", "Pick one query (default parameters)", "Pick one query (pick parameters)"));
    }

    private void makePickQueryMenu(){
        List<String> options = new ArrayList<>();
        for(int i = 1; i < 12; i++) options.add("Query " + i);
        this.pickQueryMenu = new Menu("Pick a Query", options);
    }
}
