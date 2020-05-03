
public class InsufficientStockException extends Exception{
	
	public InsufficientStockException() {
		
	}
	
	public InsufficientStockException(String errorMsg) {
		super(errorMsg);
	}
	
	@Override
	public String toString() {
		return "Not enough items in stock!";
	}

}
