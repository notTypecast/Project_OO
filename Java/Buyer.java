
public class Buyer extends User {
	
	//enum for categories
	enum CATEGORY { 
		BRONZE,
		SILVER,
		GOLD
	};
	
	private int bonus;
	private CATEGORY buyerCategory;
	private ShoppingCart cart;
	
	//Constructor initializes object with name and mail
	public Buyer(String name, String mail) throws InvalidNameLengthException {
		super(name, mail);
		//initialize bonus at 0, new shopping cart
		this.bonus = 0;
		this.cart = new ShoppingCart();
		
		//run the setBuyerCategory method
		//will initially set to BRONZE
		this.setBuyerCategory();		
	}
	
	//add points to bonus and re-evaluate the category
	public void awardBonus(int points) {
		this.bonus += points;
		
		this.setBuyerCategory();
		
	}
	
	//evaluate buyer category based on current points
	public void setBuyerCategory() {
		if (this.bonus > 200)
			this.buyerCategory = CATEGORY.GOLD;
		else if (this.bonus > 100)
			this.buyerCategory = CATEGORY.SILVER;
		else
			this.buyerCategory = CATEGORY.BRONZE;
	}
	
	//getter for buyer category
	public CATEGORY getBuyerCategory() {
		return this.buyerCategory;
	}
	
	//add a new order to the cart
	//if there isn't enough in stock, throws InsufficientStockException
	public void placeOrder(Item item, int q) throws InsufficientStockException {
		this.cart.addItem(item, q);
		
	}
	
	//getter for bonus
	public int getBonus() {
		return this.bonus;
	}
	
	//getter for shopping cart
	public ShoppingCart getShoppingCart() {
		return this.cart;
	}
	

}
