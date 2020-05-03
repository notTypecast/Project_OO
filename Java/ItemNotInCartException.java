
public class ItemNotInCartException extends Exception{
	
	public ItemNotInCartException() {
		
	}
	
	public ItemNotInCartException(String errorMsg) {
		super(errorMsg);
	}
	
	@Override
	public String toString() {
		return "That item is not in the cart!";
	}

}