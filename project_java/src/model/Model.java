package model;

import model.QueryClasses.*;
import model.QueryInterfaces.*;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.NoSuchFileException;
import java.nio.file.Paths;
import java.text.DateFormatSymbols;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

/**
 * Modelo,agrupa os dados e metodos de modelação dos mesmos
 */
public class Model implements Statistics, Query1,Query2, Query3, Query4,Query5,Query6, Query7,Query8,Query9, Query10,Serializable {
    private boolean loaded;
    private UserCat users;
    private ReviewCat reviews;
    private BusinessCat businesses;
    //dados para estatisticas
    private List<String> filesLoaded = new ArrayList<>();
    private int invalidReviews = 0;


    /**
     * Construtor de Model
     */
    public Model(){
        this.users = new UserCat();
        this.businesses = new BusinessCat();
        this.reviews = new ReviewCat();
        this.loaded = false;
    }

    /**
     * Construtor de Model
     * @param userFile ficheiro para carregar os users
     * @param businessFile ficheiro para carregar os businesses
     * @param reviewFile ficheiro para carregar as reviews
     * @param loadFriends booleano que indica se os users carregam o paramtro friends
     * @throws IOException
     */
    public Model(String userFile, String businessFile, String reviewFile,boolean loadFriends) throws IOException {
        this.loaded = false;
        this.users = new UserCat();
        this.businesses = new BusinessCat();
        this.reviews = new ReviewCat();
        load(userFile, businessFile, reviewFile,loadFriends);
    }

    /**
     * Construtor de Model
     * @param objectFile ficheiro de objetos de on de carregar
     */
    public Model(String objectFile) throws IOException, ClassNotFoundException {
        this();
        Model m = loadModel(objectFile);
        if(m != null){
            loaded = true;
            users = m.users;
            businesses = m.businesses;
            reviews = m.reviews;
            filesLoaded = m.filesLoaded;
            invalidReviews = m.invalidReviews;
        }
    }

    /**
     * Grava o estado num ficheiro de objetos
     * @param filename ficheiro onde gravar
     * @throws IOException
     */
    public void saveModel(String filename) throws IOException {
        FileOutputStream fos = new FileOutputStream(filename);
        int bufferSize = 16 * 1024;
        ObjectOutputStream oos = new ObjectOutputStream(new BufferedOutputStream(fos, bufferSize));
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }

    /**
     * le o estado de um  ficheiro de objetos
     * @param filename ficheiro de onde carregar
     * @throws IOException
     */
    public Model loadModel(String filename) throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(filename);
        int bufferSize = 16 * 1024;
        ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(fis, bufferSize));
        Model s = (Model) ois.readObject() ;
        ois.close();
        return s;
    }


    /**
     * Agrupa os varios metodos de load de ficheiros
     * @param users_file ficheiro para carregar os users
     * @param businesses_file ficheiro para carregar os businesses
     * @param reviews_file ficheiro para carregar as reviews
     * @param loadFriends booleano que indica se os users carregam o paramtro friends
     * @throws IOException
     */
    public void load(String users_file,String businesses_file, String reviews_file,boolean loadFriends) throws IOException {
        loadUsers(users_file,loadFriends);
        loadBusinesses(businesses_file);
        loadReviews(reviews_file);

        filesLoaded.add(users_file);
        filesLoaded.add(businesses_file);
        filesLoaded.add(reviews_file);
        loaded = true;
    }

    /**
     * Carregamento dos users de um ficheiro, apenas se carrega um user caso
     * o metodo de validacao do mesmo retorne true
     * @param filename ficheiro onde se vao ler os users
     * @param loadFriends booleano que indica se os friends devem ser carregados
     * @throws IOException
     */
    private void loadUsers(String filename,boolean loadFriends) throws IOException {
        List<String> lines;
        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines){
                if(User.validUser(line)){
                    User us = new User(line,loadFriends);
                   this.users.addUser(us);
                }

            }

        } catch (IOException e) {
           /* e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");*/
        }
    }

    /**
     * Carregamento dos businesses de um ficheiro, apenas se carrega um business
     * caso o metodo de validacao do mesmo retorne true
     * @param filename ficheiro onde se vao ler os businesses
     * @throws IOException
     */
    private void loadBusinesses(String filename) throws  IOException{
        List<String> lines;
        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines) {
                if (Business.validBusiness(line)) {
                    Business biz = new Business(line);
                    this.businesses.addBusiness(biz);
                }
            }

        } catch (IOException e) {
            /*e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");*/
        }
    }

    /**
     * Carregamento dos reviews de um ficheiro, apenas se carrega uma review
     * caso o metodo de validacao da mesma retorne true
     * @param filename ficheiro onde se vao ler as reviews
     */
    private void loadReviews(String filename){
        List<String> lines;
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines){
                if(Review.validReview(line)){ //validate fields of review
                    Review rev = new Review(line);
                    if(this.users.containsId(rev.getUser_id()) && this.businesses.containsId(rev.getBusiness_id())){ //check if users and businesses exist
                        this.reviews.addReview(rev);
                    }else invalidReviews++;

                }
            }

        } catch (IOException e) {
            /*e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");*/
        }

    }

    /**
     * Getter das reviews carregadas
     * @return reviews carregadas
     */
    public Map<String, Review> getReviews(){return reviews.getReviews();}

    /**
     * Getter dos businesses carregados
     * @return businesses carregados
     */
    public Map<String, Business> getBusinesses(){return businesses.getBusinesses();}

    /**
     * Getter dos users carregados
     * @return users carregados
     */
    public Map<String, User> getUsers() {
        return users.getUsers();
    }

    /**
     * Verifica se ja foram carregados dados
     * @return boolean loaded
     */
    public boolean getLoaded(){return loaded;}

    /**
     * Metodo que verifica se um certo businessId foi avaliado
     * @param businessId business a verificar
     * @return resultado da verificacao
     */
    public boolean businessReviewed(String businessId){
        return reviews.businessReviewed(businessId);
    }

    /**
     * Verifica se foi carregado um business com o dado id
     * @param b_id business a procurar
     * @return resultado da procura
     */
    public boolean existsBusiness(String b_id){return this.businesses.containsId(b_id);}

    /**
     * Verifica se foi carregado um user com o dado id
     * @param u_id user a procurar
     * @return resultado da procura
     */
    public boolean existsUser(String u_id){return this.users.containsId(u_id);}

    public NotReviewed query1(){
        NotReviewed results = new NotReviewed();
        Map<String,Business> businesses = getBusinesses();
        Map<String,Review> reviewsSearch = getReviews();

        reviewsSearch.forEach((k,v) -> {
            businesses.remove(v.getBusiness_id());
        });

        businesses.forEach((k,v) -> results.addBusiness(v));
        return results;
    }

    public ReviewedPerMonth query2(int month, int year){
        ReviewedPerMonth result = new ReviewedPerMonth();
        if(month >0 && month <13 && year<= LocalDateTime.now().getYear()){
            getReviews().forEach((s,r)->
                    {
                        LocalDateTime date =  r.getDate();
                        if(date.getYear() == year && date.getMonthValue() == month)
                            result.incTotalReviews(r.getStars(),r.getUser_id());
                    });
        }
        return result;
    }

    public ArrayList<ReviewedPerMonth> query3(String user_id){

        //contem reviews do dado user
        Map<String,Review> reviews = getReviews().values().stream()
                                    .filter((r)->r.getUser_id().equals(user_id))
                                    .collect(Collectors.toMap(Review::getReview_id, r->r));
        ArrayList<ReviewedPerMonth> reviewsByMonth= new ArrayList<>(12);

        for(int i = 0; i<12;i++) reviewsByMonth.add(new ReviewedPerMonth());
        reviews.forEach((k,v)-> {
        int month = v.getDate().getMonthValue();
        reviewsByMonth.get(month - 1).incTotalReviews(v.getStars(), v.getBusiness_id());
            }
        );

        return reviewsByMonth;
    }

    public ArrayList<ReviewedPerMonth> query4(String b_id){
        //filtrar para ter apenas as reviews sobre o negocio em questao
        Map<String,Review> reviews = getReviews().values().stream()
                .filter((r) -> r.getBusiness_id().equals(b_id))
                .collect(Collectors.toMap(Review::getReview_id, r->r));
        ArrayList<ReviewedPerMonth> monthReviews = new ArrayList<>(12);
        for (int i =0; i<12;i++) {
            monthReviews.add(new ReviewedPerMonth());
        }
        reviews.forEach((k,v) -> {
            int month = v.getDate().getMonthValue();
            monthReviews.get(month - 1).incTotalReviews(v.getStars(),v.getUser_id());
                });

        return monthReviews;
    }

    public ArrayList<ReviewsByBizName> query5(String user_id){

        Map<String,Review> reviews = getReviews().values().stream()
                                    .filter((r)->r.getUser_id().equals(user_id))
                                    .collect(Collectors.toMap(Review::getReview_id, r->r));

        Map<String,ReviewsByBizName> reviews_bizs = new HashMap<>();
        Map<String,Business> bizs = getBusinesses();


        for(Review rev : reviews.values()){
            String b_id = rev.getBusiness_id();
            if(reviews_bizs.containsKey(b_id)){
                reviews_bizs.get(b_id).incTotal();
            }else{
                reviews_bizs.put(b_id,new ReviewsByBizName(bizs.get(b_id).getName(),1));
            }
        }
        
        ArrayList<ReviewsByBizName> reviews_bizsList = new ArrayList<>(reviews_bizs.values());
        reviews_bizsList.sort(new ReviewsByBizNameComp());

        return reviews_bizsList;

    }

    public List<TopReviewsAux> query6(int top){
        TopReviews years = new TopReviews(top);
        getReviews().forEach((k,v)->{
            years.addReview(v.getDate().getYear(),v.getBusiness_id(),v.getUser_id(),v.getStars());
        });
        return years.topBus(new TopReviewsAuxComp());
    }

    public List<Query7aux> query7(){

        //Hash das diferentes cidades
        //a key sera o numero de cidades e o value sera um hashMap com os business dessa cidade
        Map<String,Map<String,Integer>> cities = new HashMap<>();
        Map<String,Business> businesses = getBusinesses();

        getReviews().forEach((k,v) ->{
            //verifica se ja existe a cidade na hash
            String b_id_search = v.getBusiness_id();
            String city= businesses.get(b_id_search).getCity();

            if(cities.containsKey(city)){
                //verifica se ja foi adicionado o business na cidade
                if(cities.get(city).containsKey(b_id_search)) {
                    int total = cities.get(city).get(b_id_search) + 1;
                    cities.get(city).replace(b_id_search, total);
                }
                else{//senao cria uma entrada para o business
                    cities.get(city).put(b_id_search,1);
                }
            }
            else{//senao cria uma entrada para essa cidade
                cities.put(city,new HashMap<String,Integer>());
                cities.get(city).put(b_id_search,1);
            }
        });

        Map<String,List<String>> results = new HashMap<>();

        //para cada cidade ordena os negocios
        // , pelo numero total de reviews feito em cada um, de forma descendente
        cities.forEach((k,v) -> {
            List<String> sortedBusinesses = v.entrySet().stream()
                    .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                    .map(Map.Entry::getKey).collect(Collectors.toList());
            //pega no maximo apenas os top 3 negocios mais famosos
            if (sortedBusinesses.size() >= 3){
                results.put(k,sortedBusinesses.subList(0,3));
            }
            else results.put(k,sortedBusinesses);

        });
        List<Query7aux> resultsList = new ArrayList<>();
        results.forEach((k,v)-> v.forEach(b -> resultsList.add(new Query7aux(k,b,cities.get(k).get(b)))));
        return resultsList;
    }

    public List<TopReviewsAux> query8(int top){
        //reutiliza a estrutura da query6 visto as querys serem bastante similares,
        //a unica diferenca e que colocara todas as reviews no mesmo ano
        TopReviews userMostReviews = new TopReviews(top);
        getReviews().forEach((k,v)->{
            userMostReviews.addReview(0,v.getUser_id(),v.getBusiness_id(),v.getStars());
        });
        //compara usando o numero total de reviews unicas
        Comparator<TopReviewsAux> comparator = new Comparator<TopReviewsAux>() {
            @Override
            public int compare(TopReviewsAux o1, TopReviewsAux o2) {
                if(o1.getUnique() == o2.getUnique()){
                    return o1.getValue().compareTo(o2.getValue());
                }else{
                    return o2.getTotal() - o1.getTotal();
                }
            }
        };
        return userMostReviews.topBus(comparator);
    }

    public List<TopReviewsAux> query9(String b_id, int top){
        TopReviews usersScore = new TopReviews(top);
        getReviews().forEach((k,v)->{
            if(v.getBusiness_id().equals(b_id))
                usersScore.addReview(0,v.getUser_id(),b_id,v.getStars());
        });
        return usersScore.topBus(new TopReviewsAuxComp());
    }

    public StateBusiness query10(){
        //hash de estados em que para cada estado tera uma hash das cidades do estado,
        //que, por sua vez terao um hash dos negocios e respetiva media
        StateBusiness states = new StateBusiness();

        Map<String,Business> businesses = getBusinesses();

        businesses.forEach((k,v) -> {
            String state = v.getState();
            String city = v.getCity();
            String b_id = v.getId();
            states.addBusiness(state,city,b_id);
        });

        //percorre as reviews e vai dando update nos scores totais do business
        //correspondente
        Map<String,Review> reviews = getReviews();
        reviews.forEach((k,v)->{
            String b_id = v.getBusiness_id();
            String state = businesses.get(b_id).getState();
            String city = businesses.get(b_id).getCity();
            float score = v.getStars();
            states.updateBusinessScore(state,city,b_id,score);
        });

        return states;

    }




    //-----------------------------ESTATISTICAS--------------------------------------------------------

    public List<String> getFilesLoaded(){
        return new ArrayList<>(filesLoaded);
    }

    public int getInvalidReviews(){return invalidReviews;}

    public int getNumberOfBusinesses(){
        return this.businesses.size();
    }

    public int getDistinctBusinessesReviewed(){
        HashMap<String,Business> reviewed = new HashMap<>();
        Map<String,Business> businesses = getBusinesses();
        Map<String,Review> reviewsSearch = getReviews();

        reviewsSearch.forEach((k,v) -> {
            reviewed.put(v.getBusiness_id(),businesses.get(v.getBusiness_id()));
        });
        return reviewed.size();
    }

    public int getNotReviewdBusinesses(){
        return query1().getTotal();
    }

    public int getNumberOfUsers(){
        return getUsers().size();
    }

    public int getNumberOfUserReviewers(){
        Set<String> userReviewer = new HashSet<>();
        getReviews().forEach((k,v) -> {
            userReviewer.add(v.getUser_id());
        });
        return userReviewer.size();
    }

    public int getUsersNotReviewers(){
        return getNumberOfUsers() - getNumberOfUserReviewers();
    }

    public int getNonImpactReviews(){
        return getReviews().values().stream().
                filter(v -> v.getCool()+v.getFunny()+v.getUseful() == 0).
                collect(Collectors.toSet()).size();
    }

    public List<ReviewedPerMonth> getReviewsPerMonth(){
        List<ReviewedPerMonth> results = new ArrayList<>(12);
        for (int i =0; i<12;i++) {
            results.add(new ReviewedPerMonth());
        }
        getReviews().forEach(
                (k,v)-> results.get(v.getDate().getMonthValue()-1).
                        incTotalReviews(v.getStars(),v.getUser_id())
                );
        return results;
    }

    public String statistics(){
        StringBuilder sb = new StringBuilder();
        sb.append("Loaded Files: ")
                .append(filesLoaded.get(0)).append(", ")
                .append(filesLoaded.get(1)).append(", ")
                .append(filesLoaded.get(2)).append("\n")
            .append("Invalid reviews: ").append(invalidReviews).append("\n")
            .append("Total businesses: ").append(getNumberOfBusinesses()).append("\n")
            .append("Distinct Reviewed Businesses: ").append(getDistinctBusinessesReviewed()).append("\n")
            .append("Not reviewed Businesses: ").append(getNotReviewdBusinesses()).append("\n")
            .append("Total Users: ").append(getNumberOfUsers()).append("\n")
            .append("Active Users: ").append(getNumberOfUserReviewers()).append("\n")
            .append("Inactive Users: ").append(getUsersNotReviewers()).append("\n")
            .append("Total Reviews: ").append(getReviews().size()).append("\n")
            .append("Unimpactful Reviews: ").append(getNonImpactReviews()).append("\n")
            .append("Reviews Per Month\n");
        AtomicInteger i = new AtomicInteger(0);
        List<ReviewedPerMonth> monthsStats = getReviewsPerMonth();
        monthsStats.forEach((v)->{
            sb.append(new DateFormatSymbols().getMonths()[i.get()])
                .append(":\n")
                .append("\tTotal Reviews: ").append(v.getTotalReviews())
                .append("\n\tAverage: ").append(v.getAverage())
                .append("\n\tUnique Users: ").append(v.getUniqueReviews())
                .append("\n");
            i.incrementAndGet();
        });
        sb.append("Global average: ")
                .append(monthsStats.stream().mapToInt(ReviewedPerMonth::getTotalReviews).sum() / 12);


        return sb.toString();
    }

}
