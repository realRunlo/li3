package queries;

import model.Business;
import model.Model;
import model.QueryClasses.NotReviewed;
import model.Review;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Classe de teste de uso de procura nas hashes
 */
public class query1Test {
    private Model data = new Model();
    private static final String objectFile = "gestReviews.dat";


    @Before
    public void setup() throws IOException, ClassNotFoundException {
        data = new Model(objectFile);
    }

    /**
     * Teste de procura de negocios com reviews
     */
    @Test
    public void query1Test(){
        double mili = (Math.pow(10,-6));

        double startTime = System.nanoTime();
        data.query1();
        double endTime = System.nanoTime();
        double timeNormal = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        query1SearchBusinessHash();
        endTime = System.nanoTime();
        double timeSearchBusinessHash = (endTime - startTime) * mili;



        System.out.println("------------Query1----------\n"+
                "Used method: " + timeNormal +" miliseconds\n"+
                "Search Business Hash: " + timeSearchBusinessHash +" miliseconds\n"+
                "-------------------------------------\n"
        );
    }

    /**
     * Percorre a hash dos negocios e, para cada, verifica
     * se existe uma review para esse negocio
     * @return resultado da query1
     */
    public NotReviewed query1SearchBusinessHash(){
        NotReviewed results = new NotReviewed();
        Map<String, Business> businesses = data.getBusinesses();
        AtomicInteger i = new AtomicInteger(0);
        businesses.forEach((k,v)->{
            if(!data.businessReviewed(v.getId())) results.addBusiness(v);
        });
        return results;
    }




}
