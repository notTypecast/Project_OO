
public class ItemNotFoundException extends Exception {
    public ItemNotFoundException(){}

    public ItemNotFoundException(String errorMsg){
        super(errorMsg);
    }

    @Override
    public String toString(){
        return "Item not found!";
    }
}