package view;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * User interface
 */
public class UI {


    /**
     * Interface para execucao de opcoes
     */
    public interface Handler {
        public void execute() throws IOException, ClassNotFoundException;
    }

    /**
     * Interface para indicar pre-condicoes para opcoes
     */
    public interface PreCondition {
        public boolean validate();
    }



    private static Scanner is = new Scanner(System.in);



    public static final String RESET = "\u001B[0m";
    public static final String BLACK = "\u001B[30m";
    public static final String RED = "\u001B[31m";
    public static final String GREEN = "\u001B[32m";
    public static final String YELLOW = "\u001B[33m";
    public static final String BLUE = "\u001B[34m";
    public static final String PURPLE = "\u001B[35m";
    public static final String CYAN = "\u001B[36m";
    public static final String WHITE = "\u001B[37m";


    private List<String> options;            // Lista de opções
    private List<PreCondition> available;  // Lista de pré-condições
    private List<Handler> handlers;         // Lista de handlers
    private boolean exit = false;

    /**
     * Construtor de UI
     * @param options menu a ser imprimido e respetivas opcoes
     */
    public UI(String[] options){
        this.options = Arrays.asList(options);
        this.available = new ArrayList<>();
        this.handlers = new ArrayList<>();
        this.options.forEach(s-> {
            this.available.add(()->true);
            this.handlers.add(()->System.out.println(RED+"Option not implemented!"+RESET));
        });
    }

    /**
     * Metodo de run simples, termina quando dado a opcao 0, ou caso
     * o booleano de control torne falso
     * Caso seja escolhido uma opcao valida e as pre-condicoes dessa opcao
     * sejam cumpridas, executa o handler respetivo
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public void SimpleRun() throws IOException, ClassNotFoundException {
        int op;
        do {
            SimpleShow();
            op = readOption();
            // testar pré-condição
            if (op>0 && !this.available.get(op).validate()) {
                System.out.println(RED +"Option not available"+ RESET);
            } else if (op>0) {
                // executar handler
                this.handlers.get(op).execute();
            }
        } while (op != 0 && !exit);
    }

    /**
     * Método que regista uma uma pré-condição numa opção do menu
     *
     * @param i índice da opção
     * @param b pré-condição a registar para a opcao
     */
    public void setPreCondition(int i, PreCondition b) {
        this.available.set(i,b);
    }

    /**
     * Similar ao metodo anterior, mas coloca a mesma pre-condicao para
     * varias opcoes ao mesmo tempo
     * @param list lista das opcoes a abrangir
     * @param b pre-condicao a registar nas opcoes
     */
    public void setSamePreCondition(int[] list, PreCondition b) {
        for(int i:list) this.available.set(i,b);

    }

    /**
     * Método para registar um handler numa opção do menu
     *
     * @param i indice da opção
     * @param h handlers a registar
     */
    public void setHandler(int i, Handler h) {
        this.handlers.set(i, h);
    }


    /**
     * Imprime as varias opcoes, verificando se as pre-condicoes estao a ser compridas
     */
    private void SimpleShow() {
        System.out.println(YELLOW + this.options.get(0) + RESET);
        for (int i=1; i<this.options.size(); i++) {
            System.out.print(i);
            System.out.print(" - ");
            System.out.println(this.available.get(i).validate() ? this.options.get(i) : "---");
        }
        System.out.println("0 - Return");
    }

    /**
     * Le uma opcao escolhida pelo user
     * @return opcao escolhida
     */
    private int readOption() {
        int op;
        //Scanner is = new Scanner(System.in);

        informationMessage("Option: ");
        try {
            String line = is.nextLine();
            op = Integer.parseInt(line);
        }
        catch (NumberFormatException e) { // Não foi inscrito um int
            op = -1;
        }
        if (op<0 || op>=this.options.size()) {
            System.out.println(RED +"Invalid Option"+RESET);
            op = -1;
        }
        return op;
    }

    /**
     * Le uma opcao escolhida pelo user entre dois limites
     * @param lower limite inferior
     * @param higher limite superior
     * @param options opcoes disponiveis
     * @return input do utilizador
     */
    public int readOptionBetween(int lower, int higher, String[] options) {
        int op = -1;
        //Scanner is = new Scanner(System.in);
        int i = 0;
        if(options != null) {
            while (i < options.length) {
                System.out.println(i + " - " + options[i]);
                i++;
            }
        }
        informationMessage("Write a number between "+lower+" and "+higher+"\nOption: ");
        while(op == -1) {
            try {
                String line = is.nextLine();
                op = Integer.parseInt(line);
            } catch (NumberFormatException e) { // Não foi inscrito um int
                op = -1;
            }
            if (op < lower || op > higher) {
                System.out.println(RED + "Invalid Option" + RESET);
                op = -1;
            }
        }
        return op;
    }

    /**
     * Faz toString de um objeto dado
     * @param o objeto a imprimir no ecra
     */
    public void showInfo(Object o){
        System.out.println(o.toString());
        informationMessage("Press any key to continue");
        is.nextLine();
    }

    /**
     * Metodo para imprimir os valores retornados das queries em formato de uma tabela
     * @param format indica o formato da tabela e o nome de cada coluna
     * @param values valores a imprimir em cada linha
     * @param page numero da pagina atual
     * @param totalPages numero total de paginas
     */
    public void printTable(List<String> format,List<List<String>> values, int page ,int totalPages){
        //descobre a string de maior comprimento
        AtomicInteger maxLength = new AtomicInteger(0);
        format.forEach(s->{
            if(s.length() > maxLength.get()) maxLength.set(s.length());
        });

        values.forEach(list->list.forEach(v->{
            if(v.length() > maxLength.get()) maxLength.set(v.length());
        }));
        maxLength.addAndGet(2); //espacamento na coluna


        StringBuilder sb = new StringBuilder();
        //imprime a primeira linha
        sb.append(printLine(maxLength.get()*format.size() + format.size()-1));
        format.forEach(f-> {
            sb.append(printColumn(f,maxLength.get()));
        });
        sb.append("|\n");

        //imprime as restantes linhas
        values.forEach(v->{
            sb.append(printLine(maxLength.get()*format.size() + format.size()-1));
            v.forEach(c->{
                sb.append(printColumn(c,maxLength.get()));
            });
            sb.append("|\n");
        });
        sb.append(printLine(maxLength.get()*format.size() + format.size()-1));
        System.out.println(sb.toString());
        System.out.println("Page "+ page+" of "+totalPages );
        System.out.println("r - return/ p - previous/ n - next\nGo to page: ");
    }

    /**
     * Auxiliar de printTable, prepara uma linha de separacao
     * @param limit tamanho da linha
     * @return linha
     */
    private String printLine(int limit){
        StringBuilder sb = new StringBuilder();
        sb.append("|");
        for (int i = 0; i<limit;i++) sb.append("-");
        sb.append("|\n");
        return sb.toString();
    }

    /**
     * Auxiliar de printTable, prepara um elemento de uma coluna
     * @param value elemento da coluna
     * @param maxLength maximo comprimento da pagina, usado para manter
     *                  todas as colunas do mesmo tamanho e centradas
     * @return coluna
     */
    private String printColumn(String value, int maxLength){
        StringBuilder sb = new StringBuilder();
        sb.append("|");
        int length =  maxLength - value.length();
        int left = length/2, right = length/2;
        if(length%2 != 0){
            left += 1;
        }
        for(int i = 0;i<left;i++) sb.append(" ");
        sb.append(value);
        for(int i = 0;i<right;i++) sb.append(" ");
        return sb.toString();
    }


    /**
     * Torna o booleano de controlo em falso, para encerrar o menu
     */
    public void returnMenu(){
        exit = true;
    }

    /**
     * Imprime uma mensagem a amarelo
     * @param message mensagem a imprimir
     */
    public void titleMessage(String message){
        System.out.println(YELLOW +message+RESET);
    }

    /**
     * Imprime uma mensagem a verde
     * @param message mensagem a imprimir
     */
    public void confirmationMessage(String message){
        System.out.println(GREEN + message + RESET);
    }

    /**
     * Imprime mensagens a roxo
     * @param message mensagem a imprimir
     */
    public void informationMessage(String message){
        System.out.println(PURPLE + message + RESET);
    }

    /**
     * Imprime mensagens na cor natural do terminal
     * @param message mensagem a imprimir
     */
    public void normalMessage(String message){
        System.out.println(message);
    }

    /**
     * Imprime mensagem a vermelho
     * @param error mensagem a imprimir
     */
    public void errorMessage(String error){
        System.out.println(RED + error + RESET);
    }

    /**
     * Metodo que limpa o terminal
     */
    public final static void clearConsole()
    {
        try
        {
            final String os = System.getProperty("os.name");

            if (os.contains("Windows"))
            {
                Runtime.getRuntime().exec("cls");
            }
            else
            {
                Runtime.getRuntime().exec("clear");
            }
        }
        catch (final Exception e)
        {
            //  Handle any exceptions.
        }
    }


}


