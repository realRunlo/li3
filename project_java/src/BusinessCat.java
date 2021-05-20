import java.util.HashMap;
import java.util.Map;

public class BusinessCat implements IBusinessCat{
    private Map<String,IBusiness> bizs;

    public BusinessCat(){
        this.bizs = new HashMap<>();
    }

    @Override
    public void addBusiness(IBusiness biz) {
        this.bizs.put(biz.getId(),biz);
    }


    public int size(){
        return this.bizs.size();
    }

}
