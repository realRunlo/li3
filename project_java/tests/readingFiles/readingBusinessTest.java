package readingFiles;

import model.Business;
import model.BusinessCat;
import model.Model;
import org.junit.Before;
import org.junit.Test;

import java.io.*;
import java.nio.CharBuffer;
import java.nio.charset.StandardCharsets;
import java.nio.file.AccessDeniedException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

/**
 * Classe de teste de leitura e carregamento de dados
 * de ficheiros assim como procura desses dados em diferentes
 * colections
 */
public class readingBusinessTest {
    private Model data = new Model();
    private static final String businessesFile = "src/input_files/business_full.csv";
    private static final String objectFile = "tests/businessObject";
    public readingBusinessTest(){}

    @Before
    public void setup() throws IOException {
        data.load("",businessesFile,"",false);
        FileOutputStream fos = new FileOutputStream(objectFile);
        int bufferSize = 16 * 1024;
        ObjectOutputStream oos = new ObjectOutputStream(new BufferedOutputStream(fos, bufferSize));
        oos.writeObject(data.getBusinesses());
        oos.flush();
        oos.close();
    }

    /**
     * Teste de diferentes leituras
     * @throws IOException
     */
    @Test
    public void loadTest() throws IOException, ClassNotFoundException {
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

        startTime = System.nanoTime();
        FileInputStream fis = new FileInputStream(objectFile);
        int bufferSize = 16 * 1024;
        ObjectInputStream ois = new ObjectInputStream(new BufferedInputStream(fis, bufferSize));
        Map<String,Business> s = (Map<String,Business>) ois.readObject() ;
        ois.close();
        endTime = System.nanoTime();
        double timeObject = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        FileInputStream fis2 = new FileInputStream(objectFile);
        ObjectInputStream ois2 = new ObjectInputStream(fis2);
        Map<String,Business> s2 = (Map<String,Business>) ois2.readObject() ;
        ois2.close();
        endTime = System.nanoTime();
        double timeObjectNoBuffer = (endTime - startTime) * mili;

        System.out.println("------------Reading----------\n"+
                "Used method: " + timeNormal +" miliseconds\n"+
                "Char by char: " + timeCharByChar +" miliseconds\n"+
                "Char by char No Buffer: " + timeCharByChar2 +" miliseconds\n"+
                "Line by line: " + timeLineByLine +" miliseconds\n"+
                "Object File (elements - "+ s.size() +"): " + timeObject +" miliseconds\n"+
                "Object File No Buffer(elements - "+ s.size() +"): " + timeObjectNoBuffer +" miliseconds\n"+
                "-------------------------------------\n"
        );
    }

    /**
     * Teste de procura de um negocio em diferentes collections
     */
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

    /**
     * Carregamento caracter a caracter com uso de um buffer
     * @throws IOException
     */
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

    /**
     * Carregamento caracter a caracter sem uso de buffer
     * @throws IOException
     */
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

    /**
     * Carregamento linha a linha
     * @throws IOException
     */
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
