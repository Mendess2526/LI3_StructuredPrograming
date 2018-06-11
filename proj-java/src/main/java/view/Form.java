package view;

import java.util.*;

class Form implements Screen<List<String>> {

    /** The name of the menu */
    private final String name;
    /** The field of the form */
    private final List<String> fields;
    /** The answers to the form */
    private final List<String> answers;

    /**
     * The Form constructor
     * @param name The form's name
     * @param fields The form's fields
     */
    Form(String name, List<String> fields){
        this.name = name;
        this.fields = fields;
        this.answers = new ArrayList<>();
    }

    /** {@inheritDoc} */
    @Override
    public Form execute(){
        System.out.println("**** " + this.name + " ****");
        Scanner is = new Scanner(System.in);
        for(String field : fields){
            System.out.println(field);
            this.answers.add(is.nextLine());
        }
        is.close();
        return this;
    }

    /** {@inheritDoc} */
    @Override
    public List<String> getResult(){
        return new ArrayList<>(this.answers);
    }
}
