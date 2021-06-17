package readingFiles;

import model.Business;
import model.BusinessCat;
import model.Model;
import org.junit.Before;
import org.junit.Test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.CharBuffer;
import java.nio.charset.StandardCharsets;
import java.nio.file.AccessDeniedException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

public class readingBusinessTest {
    private Model data = new Model();
    private static final String businessesFile = "src/input_files/business_full.csv";
    public readingBusinessTest(){}

    @Before
    public void setup() throws IOException {
        data.load("",businessesFile,"",false);
    }


    @Test
    public void loadTest() throws IOException {
        double mili = (Math.pow(10,-6));

        double startTime = System.nanoTime();
        data.load("",businessesFile,"",false);
        double endTime = System.nanoTime();
        double timeNormal = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        charByChar();
        endTime = System.nanoTime();
        double timeCharByChar = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        charByCharNoBuffer();
        endTime = System.nanoTime();
        double timeCharByChar2 = (endTime - startTime) * mili;



        startTime = System.nanoTime();
        lineByLine();
        endTime = System.nanoTime();
        double timeLineByLine = (endTime - startTime) * mili;


        System.out.println("------------Reading----------\n"+
                "Used method: " + timeNormal +" miliseconds\n"+
                "Char by char: " + timeCharByChar +" miliseconds\n"+
                "Char by char No Buffer: " + timeCharByChar2 +" miliseconds\n"+
                "Line by line: " + timeLineByLine +" miliseconds\n"+
                "-------------------------------------\n"
        );
    }

    @Test
    public void searchTest(){
        String id ="8zehGz9jnxPqXtOc7KaJxA";
        double mili = (Math.pow(10,-6));
        Map<String,Business> bus = data.getBusinesses();
        List<Business> busList = new ArrayList<>();
        Set<Business> busSet = new HashSet<>();
        bus.forEach((k,v)-> {
            busList.add(v);
            busSet.add(v);
        });

        double startTime = System.nanoTime();
        bus.containsKey(id);
        double endTime = System.nanoTime();
        double timeNormal = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        busList.stream().filter(b->b.getId().equals(id)).findFirst();
        endTime = System.nanoTime();
        double timeList = (endTime - startTime) * mili;

        Business b = bus.get(id);

        startTime = System.nanoTime();
        busList.contains(b);
        endTime = System.nanoTime();
        double timeListObject = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        busSet.stream().filter(x->x.getId().equals(id)).findFirst();
        endTime = System.nanoTime();
        double timeSet = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        busSet.contains(b);
        endTime = System.nanoTime();
        double timeSetObject = (endTime - startTime) * mili;

        System.out.println("------------Searching----------\n"+
                "Used method: " + timeNormal +" miliseconds\n"+
                "List: " + timeList +" miliseconds\n"+
                "List Object: " + timeListObject +" miliseconds\n"+
                "Set: " + timeSet +" miliseconds\n"+
                "Set Object: " + timeSetObject +" miliseconds\n"+
                "-------------------------------------\n"
        );
    }


    private void charByChar() throws IOException {
        BusinessCat businesseTestCharByChar = new BusinessCat();
        BufferedReader r = new BufferedReader(new FileReader(businessesFile));
        int c;
        StringBuilder line = new StringBuilder();
        while((c=r.read())!=-1){
            if((char) c == '\n'){
                if (Business.validBusiness(line.toString())) {
                    Business biz = new Business(line.toString());
                    businesseTestCharByChar.addBusiness(biz);
                }
                line = new StringBuilder();
            }else line.append((char) c);
        }
    }

    private void charByCharNoBuffer() throws IOException {
        BusinessCat businesseTestCharByChar = new BusinessCat();
        FileReader r = new FileReader(businessesFile);
        int c;
        StringBuilder line = new StringBuilder();
        while((c=r.read())!=-1){
            if((char) c == '\n'){
                if (Business.validBusiness(line.toString())) {
                    Business biz = new Business(line.toString());
                    businesseTestCharByChar.addBusiness(biz);
                }
                line = new StringBuilder();
            }else line.append((char) c);
        }
    }

    private void lineByLine() throws IOException {
        BusinessCat businesseLineByLine = new BusinessCat();
        BufferedReader r = new BufferedReader(new FileReader(businessesFile));
        int c;
        String line;
        while((line=r.readLine())!=null){
            if (Business.validBusiness(line)) {
                Business biz = new Business(line);
                businesseLineByLine.addBusiness(biz);
            }
        }
    }


}
