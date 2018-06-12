package view;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

import static java.util.Arrays.asList;

@SuppressWarnings({"WeakerAccess", "SameParameterValue"})
public class View {

    /** Sequencia para fazer reset as cores */
    private static final String RESET = "\033[0m";
    /** Menu principal */
    private Menu mainMenu;
    /** Menu para selecionar uma query */
    private Menu pickQueryMenu;

    /**
     * "Pinta" uma string de vermelho
     * @param s String a pintar
     * @return String pintada
     */
    static String RED(String s){
        return "\033[31m" + s + RESET;
    }
    /**
     * "Pinta" uma string de verde
     * @param s String a pintar
     * @return String pintada
     */
    static String GREEN(String s){
        return "\033[32m" + s + RESET;
    }
    /**
     * "Pinta" uma string de azul
     * @param s String a pintar
     * @return String pintada
     */
    static String BLUE(String s){
        return "\033[34m" + s + RESET;
    }
    /**
     * "Pinta" uma string de roxo
     * @param s String a pintar
     * @return String pintada
     */
    static String PURPLE(String s){
        return "\033[35m" + s + RESET;
    }
    /**
     * "Pinta" uma string de amarelo
     * @param s String a pintar
     * @return String pintada
     */
    static String YELLOW(String s){
        return "\033[33m" + s + RESET;
    }
    /**
     * Coloca uma string a negrito
     * @param s String a colocar a negrito
     * @return String a negrito
     */
    static String BOLD(String s){
        return "\033[1m" + s + RESET;
    }
    /**
     * Sublinha uma string
     * @param s String a sublinhar
     * @return String sublinhada
     */
    static String UNDERLINE(String s){
        return "\033[4m" + s + RESET;
    }

    /**
     * Executa o menu principal
     * @return A escolha do utilizador
     */
    public int runMainMenu(){
        if(this.mainMenu == null) makeMainMenu();
        this.mainMenu.execute();
        return this.mainMenu.getResult();
    }

    /**
     * Executa o menu de escolha de query
     * @return A query escolhida
     */
    public int runPickQueryMenu(){
        if(this.pickQueryMenu == null) makePickQueryMenu();
        this.pickQueryMenu.execute();
        return this.pickQueryMenu.getResult();
    }

    /**
     * Apresenta os resultados da query
     * @param queryNum O número da query
     * @param parameters Os parâmetros da query
     * @param result Os resultados da query
     * @param time O tempo que a query demorou
     */
    public void showResults(int queryNum, List parameters, Object result, long time){
        System.out.print(BOLD(GREEN("Query " + queryNum + ": ")));
        System.out.println(GREEN(parameters.toString()));
        System.out.println(YELLOW(result.toString()));
        System.out.println(PURPLE("Time taken: " + time));
    }

    /**
     * Pede o caminho do dump ao utilizador
     * @return O caminho passado
     */
    public String requestDumpPath(){
        return new Form("Insert dump path", Collections.singletonList("Dump path: "))
                .execute()
                .getResult()
                .get(0);
    }

    /**
     * Notifica que está a carregar os xml
     */
    public void notifyLoading(){
        System.out.println(BOLD(BLUE("Loading from xml...")));
    }

    /**
     * Mostra o número total de entidades criadas.
     * @param users Número de utilizadores
     * @param questions Número de questões
     * @param answers Número de respostas
     */
    public void showEntityCounts(long users, long questions, long answers){
        System.out.println(BOLD("Users:    \t") + users);
        System.out.println(BOLD("Questions:\t") + questions);
        System.out.println(BOLD("Answers:  \t") + answers);
    }

    /**
     * Pede ao utilizador para permir enter para continuar.
     */
    public void requestContinue(){
        System.out.print("Press ENTER to continue: ");
        new Scanner(System.in).nextLine();
    }

    /**
     * Executa um formulario
     * @param fields Os campos do formulario
     * @return As respostas do formulario
     */
    public List<String> runForm(List<String> fields){
        Form form = new Form("Pick parameters", fields);
        return form.execute().getResult();
    }

    /**
     * Cria o menu principal
     */
    private void makeMainMenu(){
        this.mainMenu = new Menu("Main", asList("Run all queries", "Pick one query (default parameters)",
                                                "Pick one query (pick parameters)"));
    }

    /**
     * Cria o menu de escolha de query
     */
    private void makePickQueryMenu(){
        List<String> options = new ArrayList<>();
        for(int i = 1; i < 12; i++) options.add("Query " + i);
        this.pickQueryMenu = new Menu("Pick a Query", options);
    }

    public void apresentarErro(String bold, String normal){
        System.out.println(RED(BOLD(bold)) + RED(normal));
    }
}
