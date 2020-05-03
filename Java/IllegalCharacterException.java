
public class IllegalCharacterException extends Exception {
	
	public IllegalCharacterException() {}
	
	public IllegalCharacterException(String errMsg) {
		
		super(errMsg);
		
	} 
	
	@Override
	public String toString() {
		
		return "Illegal Character : ';' " ;
	}

}
