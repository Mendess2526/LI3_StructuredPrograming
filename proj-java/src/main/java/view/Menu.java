package view;

import java.io.IOException;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

import static view.View.*;
import static view.View.UNDERLINE;

/**
 * Esta classe implementa um menu em modo texto.
 */
public class Menu implements Screen<Integer> {

    /** Menu name. */
    private final String name;
    /** Lista de opções do menu. */
    private final List<String> options;
    /** Opção selecionada. */
    private int op;

    /**
     * Cria um menu.
     *
     * @param name    Nome do menu.
     * @param options Lista das opções que pode escolher.
     */
    Menu(String name, List<String> options){
        this.name = name;
        this.options = options;
        this.op = 0;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Menu execute(){
        do{
            showMenu();
            this.op = readOption();
        }
        while(this.op == -1);
        return this;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Integer getResult(){
        return this.op;
    }

    /**
     * Imprime o menu.
     */
    private void showMenu(){
        clearScreen();
        System.out.println(UNDERLINE(RED("\n *** " + this.name + " Menu *** ")));
        for(int i = 0; i < this.options.size(); i++){
            System.out.print(BOLD(String.valueOf(i + 1)));
            System.out.print(" - ");
            System.out.println(this.options.get(i));
        }
        System.out.println(BOLD("0") + " - Exit");
    }

    /**
     * Limpa o ecrã.
     */
    private void clearScreen(){
        if(System.getProperty("os.name").equals("Linux")){
            try{
                Runtime.getRuntime().exec("clear");
                Runtime.getRuntime().exec("clear");
            }catch(IOException ignored){
            }
        }
        //System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }

    /**
     * Lê a opção escolhida.
     *
     * @return A opção escolhida.
     */
    private int readOption(){
        int op;
        Scanner is = new Scanner(System.in);

        System.out.print("Opção: ");
        try{
            op = is.nextInt();
        }catch(InputMismatchException e){ // Not an int
            op = -1;
        }
        if(op < 0 || op > this.options.size()){
            System.out.println(RED("\n=====================\n"
                                   + "  " + BOLD(UNDERLINE(RED("Opção Inválida!!!\n")))
                                   + RED("=====================")));
            op = -1;
        }
        return op;
    }
}