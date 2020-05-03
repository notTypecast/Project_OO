public class InvalidNameLengthException extends Exception {
    public InvalidNameLengthException(){}

    public InvalidNameLengthException(String errorMsg){
        super(errorMsg);
    }

    public String toString(){
        return "Name should be between 2 and 20 characters.";
    }
}