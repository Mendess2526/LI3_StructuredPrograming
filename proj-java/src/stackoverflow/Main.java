package stackoverflow;

public class Main {

    public static void main(String[] args) {
        Community com = new Community();
        Parser.parse(com, makeDumpPath(args.length > 2 ? args[1] : null));

    }

    private static String makeDumpPath(String folder){
        if(folder == null) folder = "askubuntu";
        return "../dump_exemplo/" + folder + "/";
    }
}
