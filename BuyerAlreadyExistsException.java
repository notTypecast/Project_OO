public class BuyerAlreadyExistsException extends Exception {

    public BuyerAlreadyExistsException(){};

    public BuyerAlreadyExistsException(String errorMsg){
        super(errorMsg);
    }

    @Override
    public String toString(){
        return "Buyer already exists!";
    }

}