public class NoBuyersException extends Exception {

    public NoBuyersException(){};

    public NoBuyersException(String errorMsg){
        super(errorMsg);
    }

    @Override
    public String toString(){
        return "No registered buyers found!";
    }

}
