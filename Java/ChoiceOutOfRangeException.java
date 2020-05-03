
public class ChoiceOutOfRangeException extends Exception {
	
	public ChoiceOutOfRangeException() {
		
	}
	
	public ChoiceOutOfRangeException(String errMsg) {
		super(errMsg);		
	}
	
	@Override
	public String toString() {
		return "Choice out of range!";
	}

}
