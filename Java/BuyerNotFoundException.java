public class BuyerNotFoundException extends Exception {

    public BuyerNotFoundException(){};

    public BuyerNotFoundException(String errorMsg){
        super(errorMsg);
    }

    @Override
    public String toString(){
        return "Buyer not found!";
    }

}