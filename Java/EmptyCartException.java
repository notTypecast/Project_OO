
public class EmptyCartException extends Exception {
	
	public EmptyCartException() {
		
	}
	
	public EmptyCartException(String errMsg) {
		super(errMsg);
	}
	
	@Override
	public String toString() {
		return "Cart is empty!";
	}

}
