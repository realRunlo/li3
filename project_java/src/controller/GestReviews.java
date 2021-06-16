package controller;

import model.Business;
import model.Model;
import model.QueryClasses.ReviewedPerMonth;
import view.UI;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;


public class GestReviews {
    private Model data;
    private UI messages = new UI(new String[]{});
    private final Scanner scanner = new Scanner(System.in);

    private static final String usersFile = "src/input_files/users_full.csv";
    private static final String businessesFile = "src/input_files/business_full.csv";
    private static final String reviewsFile =  "src/input_files/reviews_1M.csv";
    private static final String[] InitialMenu = new String[]{
            "Initial Menu",
            "Load State",
            "Enter Program"
    };
    private final String[] LoadDataMenu = new String[]{
            "Load Menu",
            "Default Files",
            "Costum Files"};
    private final String[] MainMenu = new String[]{
            "Main Menu",
            "Statistics",
            "Query1",
            "Query2",
            "Query3",
            "Query4",
            "Query5",
            "Query6",
            "Query7",
            "Query8",
            "Query9",
            "Query10"
    };
    /**
     * Construtor de GestReviews
     */
    public GestReviews(){
        data = new Model();
    }

    /**
     * Construtor de GestReviews
     * @param userFile ficheiro para carregar os users
     * @param businessFile ficheiro para carregar os businesses
     * @param reviewFile ficheiro para carregar as reviews
     * @throws IOException
     */
    public GestReviews(String userFile, String businessFile, String reviewFile) throws IOException {
        data = new Model(userFile,businessFile,reviewFile,false);
    }

    /**
     * Metodo que inicia os menus do programa
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public void run() throws IOException, ClassNotFoundException {
        UI initial = new UI(InitialMenu);
        initial.setPreCondition(2,()->data.getLoaded());

        initial.setHandler(1,()->loadData());
        initial.setHandler(2,()->mainMenu());

        initial.SimpleRun();
    }

    /**
     * Menu de carregamento de dados
     * @throws IOException
     * @throws ClassNotFoundException
     */
    private void loadData() throws IOException, ClassNotFoundException {
        UI load = new UI(LoadDataMenu);

        load.setHandler(1,()->{
            load(true);
            load.returnMenu();
        });
        load.setHandler(2,()->{
            load(false);
            load.returnMenu();
        });
        load.SimpleRun();
    }

    /**
     * Carregamento de dados
     * @param defaultFiles indica se o carregamento de dados
     *                     sera atraves dos ficheiros default
     *                     ou escolhidos pelo utilizador
     */
    private void load(boolean defaultFiles){
        String u_file = usersFile;
        String b_file = businessesFile;
        String r_file = reviewsFile;
        if(!defaultFiles){
            messages.informationMessage("Insert user file");
            u_file = scanner.nextLine();
            messages.informationMessage("Insert business file");
            b_file = scanner.nextLine();
            messages.informationMessage("Insert review file");
            r_file = scanner.nextLine();
        }
        boolean loadFriends = getBoolean("Do you wish to load users friends?");
        try {
            messages.normalMessage("Loading");
            this.data = new Model(u_file,b_file,r_file,loadFriends);
            messages.confirmationMessage("Files Loaded");
        } catch(FileNotFoundException e){
            messages.errorMessage("File not found");
        }
        catch(IOException e){
            messages.errorMessage("Error accessing the file");
        }
    }

    /**
     * Menu principal do programa, onde se podera utilizar as diversas
     * queries e analisar as estatisticas dos dados
     * @throws IOException
     * @throws ClassNotFoundException
     */
    private void mainMenu() throws IOException, ClassNotFoundException {
        UI main = new UI(MainMenu);

        main.setSamePreCondition(new int[]{3,4,5,6,7,8,9,10,11},()->false);

        main.setHandler(1,()->messages.showInfo(data.statistics()));
        main.setHandler(2,()->query1());


        main.SimpleRun();
    }




    public void query1(){
        List<Business> query1 = new ArrayList<>(data.query1().getNotReviewed());
        int size = query1.size();
        boolean valid = false, validPage = true;
        int page = 0,currentPage = 0, valuesPage = 10, totalPages = size/valuesPage;
        String line = "";
        List<String> format = new ArrayList<>();
        format.add("Business_name");

        while(!valid){
            int i = 0;
            if((valuesPage*page+i)>size) page = currentPage;
            currentPage = page;
            List<List<String>> values = new ArrayList<>();
            //vai buscar os elementos para imprimir na pagina
            while(i<valuesPage && (valuesPage*page+i)<size){
                List<String> business = new ArrayList<>();
                business.add(query1.get((valuesPage*page+i)).getName());
                values.add(business);
                i++;
            }
            //imprime a pagina
            messages.printTable(format,values,page,totalPages);

            //pede pelo input de uma nova pagina ou para retornar
            try {
                line = scanner.nextLine();
                page = Integer.parseInt(line);
                validPage = true;
            } catch (NumberFormatException e) { // Não foi escrito um int
                page = currentPage;
                validPage = false;
            }
            if(line.equals("r") || line.equals("return")){
                valid = true;
            }else if(line.equals("n")) page++;
            else if(line.equals("p")) page--;
            else if(!validPage) messages.errorMessage("Insert a valid command");
        }
    }





    //TODO: metodo de teste,apagar para entrega
    public void teste(int teste){
        if(teste == 1 ) System.out.println(data.query1().toString());
        if(teste == 4) {
            ArrayList<ReviewedPerMonth> months = data.query4("8zehGz9jnxPqXtOc7KaJxA");
            months.forEach(k->System.out.println(k.toString()));
        }
        if(teste == 7){
            data.query7().forEach((k,v) -> {System.out.println();
                System.out.println(k);
                v.forEach(System.out::println);
            });
        }
        if(teste ==10){
            System.out.println(data.query10().toString());
        }
    }




//------------------------------------GENERAL METHODS--------------------------------

    /**
     * Metodo que pede e recebe um boolean do utilizador
     * @param message mensagem a ser passada no pedido do boolean
     * @return input do utilizador
     */
    private boolean getBoolean(String message){
        boolean bol = false;
        boolean valid = false;
        String input = "";
        while(!valid){
         messages.informationMessage(message + "[y/n]");
         input = scanner.nextLine();
         if(input.equals("y") || input.equals("Y") || input.equals("yes")){
             valid = true;
             bol = true;
         }
         if(input.equals("n") || input.equals("N") || input.equals("no")){
             valid = true;
         }
        }
        return bol;
    }


}
