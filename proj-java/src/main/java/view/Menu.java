package view;

import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

/**
 * Esta classe implementa um menu em modo texto.
 */
public class Menu implements Screen<Integer> {

    /** Menu name */
    private final String name;
    /** List of options of the menu */
    private final List<String> options;
    /** Selected option */
    private int op;

    /**
     * Constructor for objects of class Menu
     * @param name    Name of the menu
     * @param options List of options from which to pick
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
            //clearScreen();
            showMenu();
            this.op = readOption();
        }
        while(this.op == -1);
        return this;
    }

    /**
     * Shows the menu
     */
    private void showMenu(){
        //clearScreen();
        System.out.println("\n *** " + this.name + " Menu *** ");
        for(int i = 0; i < this.options.size(); i++){
            System.out.print(i + 1);
            System.out.print(" - ");
            System.out.println(this.options.get(i));
        }
        System.out.println("0 - Exit");
    }

    /**
     * Clears the screen
     */
    private void clearScreen(){
        System.out.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }

    /**
     * Reads the users option
     * @return reads an option
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
            System.out.println("Opção Inválida!!!");
            op = -1;
        }
        is.close();
        return op;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public Integer getResult(){
        return this.op;
    }
}