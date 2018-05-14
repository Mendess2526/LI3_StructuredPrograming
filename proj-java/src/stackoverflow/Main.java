package stackoverflow;

public class Main {

    public static void main(String[] args) {
        Parser.parse(new Community(), makeDumpPath(args.length > 2 ? args[1] : null));
    }

    private static String makeDumpPath(String folder){
        if(folder == null) folder = "askubuntu";
        return System.getProperty("user.home") + "/dump_exemplo/" + folder + "/";
    }
}
