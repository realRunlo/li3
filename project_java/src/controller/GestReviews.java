package controller;

import model.Business;
import model.Model;
import model.QueryClasses.*;
import view.UI;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.DateFormatSymbols;
import java.util.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;
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

        main.setSamePreCondition(new int[]{3,6,7,9,10},()->false);

        main.setHandler(1,()->messages.showInfo(data.statistics()));
        main.setHandler(2, this::query1);
        main.setHandler(4,()->teste(3));
        main.setHandler(5, this::query4);
        main.setHandler(8, this::query7);
        main.setHandler(11, this::query10);

        main.SimpleRun();
    }


    /**
     * Executa a query1 e faz os passos necessarios de modo
     * a tornar os resultados obtidos paginaveis
     */
    private void query1(){
        List<String> format = turnFormat(new String[]{"Business_name"});
        List<Business> query1 = new ArrayList<>(data.query1().getNotReviewed());
        int size = query1.size();
        AtomicBoolean valid = new AtomicBoolean(false);
        AtomicInteger page = new AtomicInteger(0), currentPage = new AtomicInteger(0);
        int valuesPage = 10, totalPages = size / valuesPage;
        AtomicReference<String> line = new AtomicReference<>("");

        while(!valid.get()){
            int i = 0;
            if (page.get() < 0) page.set(0);
            int element = valuesPage * page.get() + i;
            if (element > size){
                page.set(currentPage.get());
                element = valuesPage * page.get() + i;
            }
            currentPage.set(page.get());
            List<List<String>> values = new ArrayList<>();

            //vai buscar os elementos para imprimir na pagina
            while(i<valuesPage && element<size){
                List<String> business = new ArrayList<>();
                business.add(query1.get((element)).getName());
                values.add(business);
                i++;
                element = valuesPage * page.get() + i;
            }
            //imprime a pagina
            messages.printTable(format, values, page.get(), totalPages);
            getPage(page,currentPage,line,valid);
        }
    }

    /**
     * Executa a query4 e faz os passos necessarios de modo
     * a tornar os resultados obtidos paginaveis
     */
    private void query4(){
        String b_id = getString("Insert a businessId to analyse reviews on it by month");
        if(data.existsBusiness(b_id)) {
            List<String> format = turnFormat(new String[]{"Month","Total Reviews","Unique Users","Average Score"});
            ArrayList<ReviewedPerMonth> query4 = data.query4(b_id);
            int size = query4.size();
            AtomicBoolean valid = new AtomicBoolean(false);
            AtomicInteger page = new AtomicInteger(0), currentPage = new AtomicInteger(0);
            int valuesPage = 10, totalPages = size / valuesPage;
            AtomicReference<String> line = new AtomicReference<>("");
            int total = 0,unique = 0;float average =0;

            while (!valid.get()) {
                int i = 0;
                if (page.get() < 0) page.set(0);
                int element = valuesPage * page.get() + i;
                if (element > size){
                    page.set(currentPage.get());
                    element = valuesPage * page.get() + i;
                }
                currentPage.set(page.get());
                List<List<String>> values = new ArrayList<>();

                //vai buscar os elementos para imprimir na pagina
                while (i < valuesPage && element < size) {
                    List<String> month = new ArrayList<>();
                    month.add(monthString(element));
                    total = query4.get((element)).getTotalReviews();
                    unique = query4.get((element)).getUniqueReviews();
                    average = query4.get((element)).getAverage();
                    month.add(String.valueOf(total));
                    month.add(String.valueOf(unique));
                    month.add(String.valueOf(average));
                    values.add(month);
                    i++;
                    element = valuesPage * page.get() + i;
                }
                //imprime a pagina
                messages.printTable(format, values, page.get(), totalPages);
                getPage(page,currentPage,line,valid);
            }
        }else messages.errorMessage("Invalid business id");
    }

    /**
     * Executa a query7 e faz os passos necessarios de modo
     * a tornar os resultados obtidos paginaveis
     */
    private void query7(){
        List<String> format = turnFormat(new String[]{"City","Business_name"});
        List<Query7aux> query7 = data.query7();
        int size = query7.size();
        AtomicBoolean valid = new AtomicBoolean(false);
        AtomicInteger page = new AtomicInteger(0), currentPage = new AtomicInteger(0);
        int valuesPage = 10, totalPages = size / valuesPage;
        AtomicReference<String> line = new AtomicReference<>("");

        while (!valid.get()) {
            int i = 0;
            if (page.get() < 0) page.set(0);
            int element = valuesPage * page.get() + i;
            if (element > size){
                page.set(currentPage.get());
                element = valuesPage * page.get() + i;
            }
            currentPage.set(page.get());
            List<List<String>> values = new ArrayList<>();

            //vai buscar os elementos para imprimir na pagina
            while (i < valuesPage && element < size) {
                List<String> business = new ArrayList<>();
                business.add(query7.get(element).getCity());
                business.add(query7.get(element).getB_name());
                values.add(business);
                i++;
                element = valuesPage * page.get() + i;
            }
            //imprime a pagina
            messages.printTable(format, values, page.get(), totalPages);
            getPage(page,currentPage,line,valid);
        }
    }


    /**
     * Executa a query10 e faz os passos necessarios de modo
     * a tornar os resultados obtidos paginaveis
     */
    private void query10(){
        List<String> format = turnFormat(new String[]{"State","City","Business Id","Average Score"});
        List<StateBusinessAux> query10 = data.query10().toList();
        int size = query10.size();
        AtomicBoolean valid = new AtomicBoolean(false);
        AtomicInteger page = new AtomicInteger(0), currentPage = new AtomicInteger(0);
        int valuesPage = 10, totalPages = size / valuesPage;
        AtomicReference<String> line = new AtomicReference<>("");

        while (!valid.get()) {
            int i = 0;
            if (page.get() < 0) page.set(0);
            int element = valuesPage * page.get() + i;
            if (element > size){
                page.set(currentPage.get());
                element = valuesPage * page.get() + i;
            }

            currentPage.set(page.get());
            List<List<String>> values = new ArrayList<>();

            //vai buscar os elementos para imprimir na pagina
            while (i < valuesPage && element < size) {
                List<String> business = new ArrayList<>();
                business.add(query10.get(element).getState());
                business.add(query10.get(element).getCity());
                business.add(query10.get(element).getId());
                business.add(String.valueOf(query10.get(element).getBusinessReviews().calcAverage()));
                values.add(business);
                i++;
                element = valuesPage * page.get() + i;
            }
            //imprime a pagina
            messages.printTable(format, values, page.get(), totalPages);
            getPage(page,currentPage,line,valid);

        }
    }

    private void getPage(AtomicInteger page, AtomicInteger currentPage, AtomicReference<String> line,AtomicBoolean valid){
        boolean validPage = true;
        //pede pelo input de uma nova pagina ou para retornar
        try {
            line.set(scanner.nextLine());
            page.set(Integer.parseInt(line.get()));
            validPage = true;
        } catch (NumberFormatException e) { // Não foi escrito um int
            page.set(currentPage.get());
            validPage = false;
        }
        if (line.get().equals("r") || line.get().equals("return")) {
            valid.set(true);
        } else if (line.get().equals("n")) page.incrementAndGet();
        else if (line.get().equals("p")) page.decrementAndGet();
        else if (!validPage) messages.errorMessage("Insert a valid command");
    }



    //TODO: metodo de teste,apagar para entrega
    public void teste(int teste){
        if(teste == 1 ) System.out.println(data.query1().toString());
        if(teste == 3){
            ArrayList<UserReviewsByMonth> users = data.query3("rKmD1FKz-XXD7spAgMCKDg");
            users.forEach(u-> System.out.println(u.getTotalReviews() +", "+u.getVariety()+", "+u.getAverage()));
        }
        if(teste == 4) {
            ArrayList<ReviewedPerMonth> months = data.query4("8zehGz9jnxPqXtOc7KaJxA");
            months.forEach(k->System.out.println(k.toString()));
        }
        if(teste == 7){
            data.query7().forEach(k -> {System.out.println();
                System.out.println(k.getCity() +" "+k.getB_name());
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

    /**
     * Dado um inteiro devolve o mes correspondente
     * @param i inteiro a ser transformado em mes
     * @return mes
     */
    private String monthString(int i){
        return new DateFormatSymbols().getMonths()[i];
    }

    /**
     * Torna um arreio de string em um lista de strings
     * utilizado para criar um argumento para a linha das colunas
     * de printTable
     * @param columns arreio de strings
     * @return arreio em formato list
     */
    private List<String> turnFormat(String[] columns){
        List<String> format = new ArrayList<>();
        for(String s:columns) format.add(s);

        return format;
    }


    /**
     * Metodo que pede ao utilizador que indique um nome
     * @return nome escolhido pelo utilizador
     */
    private String getString(String message){
        messages.informationMessage(message);
        return scanner.nextLine();
    }


}
