package queries;

import model.Model;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;

/**
 * Classe de teste de performance das queries
 */
public class performanceTest {
    private Model data;
    private static final String object = "gestReviews.dat";
    private static final double mili = (Math.pow(10, -6));

    @Before
    public void setup() throws IOException, ClassNotFoundException {
        data = new Model(object);
    }


    /**
     * Testes de performance da query1
     */
    @Test
    public void query1Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query1();
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double time = total/10;

        System.out.println(
                "------------Query1----------\n"+
                "Query1 : " + time +" miliseconds\n"+
                "----------------------------\n"
        );
    }

    /**
     * Testes de performance da query2
     */
    @Test
    public void query2Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query2(1,2010);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double time = total/10;

        System.out.println(
                "------------Query2----------\n"+
                "Query2 : " + time +" miliseconds\n"+
                "----------------------------\n"
        );
    }

    /**
     * Testes de performance da query3
     */
    @Test
    public void query3Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query3("ak0TdVmGKo4pwqdJSTLwWw");
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeFewReviews = total/10;
        total=0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query3("RtGqdDBvvBCjcu5dUqwfzA");
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeLotsOfReviews = total/10;

        System.out.println(
                "------------Query3----------\n"+
                        "Few Reviews: " + timeFewReviews +" miliseconds\n"+
                        "Lots of Reviews : " + timeLotsOfReviews +" miliseconds\n"+
                        "----------------------------\n"
        );
    }


    /**
     * Testes de performance da query4
     */
    @Test
    public void query4Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query4("8zehGz9jnxPqXtOc7KaJxA");
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double time = total/10;

        System.out.println(
                "------------Query4----------\n"+
                "query4 : " + time +" miliseconds\n"+
                "----------------------------\n"
        );
    }

    /**
     * Testes de performance da query5
     */
    @Test
    public void query5Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query5("RtGqdDBvvBCjcu5dUqwfzA");
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double time = total/10;

        System.out.println(
                "------------Query5----------\n"+
                        "query5 : " + time +" miliseconds\n"+
                        "----------------------------\n"
        );
    }


    /**
     * Testes de performance da query6
     */
    @Test
    public void query6Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query6(1);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop1 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query6(10);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop10 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query6(100);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop100 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query6(1000);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop1000 = total/10;

        System.out.println(
                "------------Query6----------\n"+
                "top 1 : " + timeTop1 +" miliseconds\n"+
                "top 10 : " + timeTop10 +" miliseconds\n"+
                "top 100 : " + timeTop100 +" miliseconds\n"+
                "top 1000 : " + timeTop1000 +" miliseconds\n"+
                "----------------------------\n"
        );
    }

    /**
     * Testes de performance da query7
     */
    @Test
    public void query7Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query7();
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double time = total/10;


        System.out.println(
                "------------Query7----------\n"+
                        "query7 : " + time +" miliseconds\n"+
                        "----------------------------\n"
        );
    }

    /**
     * Testes de performance da query8
     */
    @Test
    public void query8Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query8(1);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop1 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query8(10);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop10 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query8(100);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop100 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query8(1000);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop1000 = total/10;

        System.out.println(
                "------------Query8----------\n"+
                        "top 1 : " + timeTop1 +" miliseconds\n"+
                        "top 10 : " + timeTop10 +" miliseconds\n"+
                        "top 100 : " + timeTop100 +" miliseconds\n"+
                        "top 1000 : " + timeTop1000 +" miliseconds\n"+
                        "----------------------------\n"
        );
    }

    /**
     * Testes de performance da query9
     */
    @Test
    public void query9Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query9("8zehGz9jnxPqXtOc7KaJxA",1);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop1 = total/10;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query9("8zehGz9jnxPqXtOc7KaJxA",10);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop10 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query9("8zehGz9jnxPqXtOc7KaJxA",100);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop100 = total/10;
        total = 0;

        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query9("8zehGz9jnxPqXtOc7KaJxA",1000);
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double timeTop1000 = total/10;

        System.out.println(
                "------------Query9----------\n"+
                        "top 1 : " + timeTop1 +" miliseconds\n"+
                        "top 10 : " + timeTop10 +" miliseconds\n"+
                        "top 100 : " + timeTop100 +" miliseconds\n"+
                        "top 1000 : " + timeTop1000 +" miliseconds\n"+
                        "----------------------------\n"
        );
    }

    /**
     * Testes de performance da query10
     */
    @Test
    public void query10Test(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.query10();
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double time = total/10;

        System.out.println(
                "------------Query10----------\n"+
                "query 10 : " + time +" miliseconds\n"+
                "----------------------------\n"
        );
    }

    /**
     * Testes de performance das estatisticas
     */
    @Test
    public void statisticsTest(){
        double total = 0;
        double startTime = 0;
        double endTime = 0;
        for(int i = 0;i<10;i++) {
            startTime = System.nanoTime();
            data.statistics();
            endTime = System.nanoTime();
            total += (endTime - startTime) * mili;
        }
        double time = total/10;

        System.out.println(
                "------------Statistics----------\n"+
                        "statistics : " + time +" miliseconds\n"+
                        "----------------------------\n"
        );
    }



}
