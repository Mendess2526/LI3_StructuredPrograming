package view;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import static view.View.RED;
import static view.View.UNDERLINE;


/**
 * Classe que define um formulário.
 */
class Form implements Screen<List<String>> {

    /** Nome do menu. */
    private final String name;
    /** Campos do formulário. */
    private final List<String> fields;
    /** Respostas do formulário. */
    private final List<String> answers;

    /**
     * Cria um formulário.
     *
     * @param name   O nome do formulário.
     * @param fields Os campos do formulário.
     */
    Form(String name, List<String> fields){
        this.name = name;
        this.fields = fields;
        this.answers = new ArrayList<>();
    }


    /**
     * {@inheritDoc}
     */
    @Override
    public Form execute(){
        System.out.println(UNDERLINE(RED("**** " + this.name + " ****")));
        Scanner is = new Scanner(System.in);
        for(String field : fields){
            System.out.println(field);
            this.answers.add(is.nextLine());
        }
        return this;
    }


    /**
     * {@inheritDoc}
     */
    @Override
    public List<String> getResult(){
        return new ArrayList<>(this.answers);
    }
}
