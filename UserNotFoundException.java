public class UserNotFoundException extends Exception {
    
    public UserNotFoundException(){}

    public UserNotFoundException(String errorMsg){
        super(errorMsg);
    }

    public String toString(){
        return "User not found!";
    }

}