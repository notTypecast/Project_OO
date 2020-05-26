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
			if (this.orderedItems.containsKey(item)){
				q += this.orderedItems.get(item);
			}
			this.orderedItems.put(item, q);
		}
		
		else
			throw new InsufficientStockException();
		
		
	}
	
	//remove from map instead of iterator
	//used for when it is required to remove a single item (no iteration)
	public void removeItem(Item item) throws ItemNotInCartException {
		this.removeItem(item, null);
	}
	
	//removes an passed item from the cart
	//throws exception for when the given item doesn't exist in the cart
	private void removeItem(Item item, Iterator<Item> iterator) throws ItemNotInCartException {
		
		boolean found = false;
		
		//iterate through pairs of keys and values in hashmap
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			//compare the keys of given item with each item of hashmap
			if (entry.getKey().getId() == item.getId()) {
				//if null was passed as an iterator
				if (iterator == null)
					//remove item from map
					orderedItems.remove(entry.getKey());
				//if an iterator was passed
				else
					//remove the next iterator item
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
	
	
	//changes the stock of an item
	//throws ItemNotInCartException if passed item doesn't exist in cart
	public void editOrderedQuantity(Item item, int newQ) throws ItemNotInCartException, InsufficientStockException {
		
		boolean found = false;
		
		
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			if (entry.getKey().getId() == item.getId()) {
				// leftover is current stock plus the ordered quantity returned to stock minus the new value
				int leftover_stock = item.getStock() + entry.getValue() - newQ;
		
				if (leftover_stock < 0)
					throw new InsufficientStockException();

				//if item is in cart replace it's quantity to the given number
				this.orderedItems.replace(entry.getKey(), newQ);
				entry.getKey().setStock(leftover_stock);
				found = true;
				break;
			}
		}
		
		if (!found)
			throw new ItemNotInCartException();
		
	}
	
	//shows cart data
	//throws EmptyCartException if the cart has no items in it
	public void showCart(Buyer.CATEGORY category) throws EmptyCartException {
	
		int i = 1;
		//iterate through Map entries
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			//print all data related to entry
			System.out.print(i + ".");
			String out = "Item: ";
			out += entry.getKey().getName() + ", price per unit: " + entry.getKey().getPrice()
					+ ", quantity: " + entry.getValue() + ", total price: " + 
					entry.getKey().getPrice() * entry.getValue() + "\n";
			
			System.out.println(out);
			
			++i;
		}
		
		if (i == 1)
			throw new EmptyCartException();
		
		//print out the total and the courrier cost
		System.out.println("Total: " + this.calculateNet());
		System.out.println("Courier cost: " + this.calculateCourierCost(category));
		
		
	}
	
	//clears the cart
	//uses iterator in order to remove items from the Map while iterating
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
	
	//checks out
	//throws EmptyCartException if there are no items in the cart
	public void checkout(Buyer buyer) throws EmptyCartException {
		
		this.showCart(buyer.getBuyerCategory());
		
		//get a y/n answer
		while (true) {
			String ans = Menu.getUserInput("Are you sure you would like to check out (y/n)? ").toLowerCase();
			
			if (ans.compareTo("y") == 0)
				break;
			
			else if (ans.compareTo("n") == 0)
				return;
						
			else
				System.out.println("Expected y/n.");
		}

		//add the bonus and clear the cart
		int bonus = (int) (0.1 * this.calculateNet()); 
		
		buyer.awardBonus(bonus);
		
		this.orderedItems.clear();
		
		System.out.println("Checked out successfully!");
		
	}
	
	
	//calculates the total price of all the cart items
	public double calculateNet() {
		
		double total = 0.0;
		
		for (Map.Entry<Item, Integer> entry: this.orderedItems.entrySet()) {
			total += entry.getKey().getPrice() * entry.getValue();
		}
		
		return total;
		
	}
	
	//calculates the courrier cost for the cart items
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
	
	//getter for orderedItems
	public Map<Item, Integer> getOrderedItems() {
		return this.orderedItems;
	}
	
	
}
