
public class ItemAlreadyExistsException extends Exception {

    public ItemAlreadyExistsException(){}

    public ItemAlreadyExistsException(String errorMessage){
        super(errorMessage);
    }

    @Override
    public String toString(){
        return "Item already exists!";
    }
}