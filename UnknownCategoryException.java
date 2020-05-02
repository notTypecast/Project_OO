
public class UnknownCategoryException extends Exception {
	
	public UnknownCategoryException() {
			
	}
	
	public UnknownCategoryException(String errMsg) {
		super(errMsg);		
	}
	
	@Override
	public String toString() {
		return "Unknown category!";
	}

}
