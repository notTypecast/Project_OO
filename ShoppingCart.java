import java.util.*;


public class ShoppingCart {
	
	//HashMap mapping items to their quantities
	private Map<Item, Integer> orderedItems;
	
	public ShoppingCart() {
		orderedItems = new LinkedHashMap<Item, Integer>();
	}
	
	
	//throws exception when there aren't enough items in stock
	public void addItem(Item item, int q) throws InsufficientStockException {
		//figure out the leftover stock after quantity is subtracted
		int leftover_stock = item.getStock() - q;
		
		if (leftover_stock >= 0) {
			item.setStock(leftover_stock);
			this.orderedItems.put(item, q);
		}
		
		else
			throw new InsufficientStockException();
		
		
	}
	
	//remove from iterator instead of from map
	//used for when removing while iterating for clear
	public void removeItem(Item item) throws ItemNotInCartException {
		this.removeItem(item, null);
	}
	
	//throws exception for when the given item doesn't exist in the cart
	private void removeItem(Item item, Iterator<Item> iterator) throws ItemNotInCartException {
		
		boolean found = false;
		
		//iterate through pairs of keys and values in hashmap
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			//compare the keys of given item with each item of hashmap
			if (entry.getKey().getId() == item.getId()) {
				//if the keys match, remove the item and break the loop
				if (iterator == null)
					orderedItems.remove(entry.getKey());
				else
					iterator.remove();
				//update the item's stock by adding the quantity being removed to it
				entry.getKey().setStock(entry.getKey().getStock() + entry.getValue());
				found = true;
				break;
			}
		}
		
		//if no keys matched, throw an exception that the item didn't exist
		if (!found)
			throw new ItemNotInCartException();
		
	}
	
	
	public void changeItemQuantity(Item item, int newQ) throws ItemNotInCartException {
		
		boolean found = false;
		
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			if (entry.getKey().getId() == item.getId()) {
				//if item is in cart, replace it's quantity to the given number
				this.orderedItems.replace(entry.getKey(), newQ);
				found = true;
				break;
			}
		}
		
		if (!found)
			throw new ItemNotInCartException();
		
	}
	
	public void showCart(Buyer.CATEGORY category) throws EmptyCartException {
	
		int i = 1;
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			System.out.println(i + ".");
			String out = "Item: ";
			out += entry.getKey().getName() + ", price per unit: " + entry.getKey().getPrice()
					+ ", quantity: " + entry.getValue() + ", total price: " + 
					entry.getKey().getPrice() * entry.getValue() + "\n";
			
			System.out.println(out);
			
			++i;
		}
		
		System.out.println("Total: " + this.calculateNet());
		System.out.println("Courier cost: " + this.calculateCourierCost(category));
		
		if (i == 1)
			throw new EmptyCartException();
		
		
	}
	
	public void clearCart() {
		
		//create an iterator of the hashmap keys, to be able to iterate and remove
		Iterator<Item> iterator = this.orderedItems.keySet().iterator();
		
		//iterate through the hashmap keys and remove each one
		while (iterator.hasNext()) {
			try {
				Item item = iterator.next();
				this.removeItem(item, iterator);
			}
			//the items are taken from the hashmap itself, so this catch block will never be run
			catch (ItemNotInCartException exc) {}
		}
		
	}
	
	public void checkout(Buyer buyer) throws EmptyCartException {
		
		this.showCart(buyer.getBuyerCategory());
		
		while (true) {
			String ans = Menu.getUserInput("Are you sure you would like to check out (y/n)? ").toLowerCase();
			
			if (ans.compareTo("y") == 0)
				break;
			
			else if (ans.compareTo("n") == 0)
				return;
						
			else
				System.out.println("Expected y/n.");
		}

		int bonus = (int) (0.1 * this.calculateNet()); 
		
		buyer.awardBonus(bonus);
		
		this.orderedItems.clear();
		
	}
	
	public double calculateNet() {
		
		double total = 0.0;
		
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			total += entry.getKey().getPrice() * entry.getValue();
		}
		
		return total;
		
	}
	
	public double calculateCourierCost(Buyer.CATEGORY category) {
		float modifier = 0.0f;
		double total;
		
		switch (category) {
			case BRONZE:
				modifier = 1.0f;
				break;
			case SILVER:
				modifier = 0.5f;
				break;
			case GOLD:
				return 0.0;
		}
		
		total = this.calculateNet() * 0.02;
		
		if (total < 3.0)
			total = 3.0;
		
		return total * modifier;
		
	}
	
	public Map<Item, Integer> getOrderedItems() {
		return this.orderedItems;
	}
	
	
}
