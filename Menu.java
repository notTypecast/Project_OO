import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Menu {
	
	public static Scanner s = new Scanner(System.in);
	
	private String regex_pattern = "^([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$";
	private Pattern p;
	private Matcher m;
	
	private HashMap<String, Runnable> commandsMap;
	
	private EShop eshop;
	
	public Menu(EShop eshop) {
		this.eshop = eshop;
		
		this.p = Pattern.compile(this.regex_pattern);
		this.commandsMap = new HashMap<String, Runnable>();
	}
	
	public static String getUserInput(String outputMsg) {
		
		String input;	
		System.out.print(outputMsg);
		input = Menu.s.nextLine();
		return input;
		
	}
	
	private void runLoop() {
		
		String command;
		
		while (true) {
			
			command = getUserInput(">> ");
			boolean foundCommand = false;
			
			for (Map.Entry<String, Runnable> entry: this.commandsMap.entrySet()) {
				
				if (command.compareTo(entry.getKey()) == 0) {
					
					entry.getValue().run();
					foundCommand = true;
					
				}
			}
			
			
			if (!foundCommand) {
				
				if (command.compareTo("help") == 0) {
					
					System.out.println("Available commands: ");
					
					for (String s: this.commandsMap.keySet()) {
						System.out.println("->" + s);
					}
					
				}
				
				else {
					System.out.println("Unknown command! Use >>help for a list of available commands.");
				}
			}
			
		}
		
	}
	
	private void browse(User user) {
		
		System.out.println("Now browsing: USER!!!");
		
		System.out.println("Shop name: " + this.eshop.getName());
		this.eshop.showCategories();
		
		List<String> categories = this.eshop.getCategories();
		
		String choice;
		
		while (true) {
			choice = Menu.getUserInput("Choose a category: ").toLowerCase();
			try {
				
				if (categories.contains(choice)) {
					break;
				}
				else if (choice.toLowerCase().equals("back")) {
					return;

				}
				
				throw new UnknownCategoryException();
				
			}
			
			catch (UnknownCategoryException e) {
				
				System.out.println(e.toString());
				
			}
		}
		
		this.browseCategory(user, choice);
		
	}
	
	private void browseCategory(User user, String choice) {
		
		String input;
		int c;
		
		this.eshop.showProductsInCategory(choice);
		
		Item chosenItem;
		
		while (true) {
			input = Menu.getUserInput("Item ID: ");
			
			try {
				
				if (input.compareTo("back") == 0) {
					this.browse(user);
					return;
				}
				
				c = Integer.parseInt(input);
				
				chosenItem = this.eshop.getItemById(c);
				
				break;
				
			}
			
			catch (NumberFormatException e) {
				System.out.println("Insert a valid ID!");
			}
			
			catch (ItemNotFoundException e) {
				System.out.println(e.toString());						
			}
		}
		
		System.out.println(chosenItem.toString());
		
		if (user instanceof Buyer) {
			buyerPlaceOrder((Buyer) user, chosenItem, choice);
		} else {
			ownerEditItem((Owner) user, chosenItem, choice);
		}
		
	}
	
	private void buyerPlaceOrder(Buyer buyer, Item chosenItem, String choice) {
		String input;
		int c;
		while (true) {
			
			System.out.print("Would you like to place an order for this item (y/n)? ");
			input = Menu.s.nextLine().toLowerCase();
			
			if (input.compareTo("y") == 0) {
				
				while (true) {
					
					System.out.print("Quantity (blank for 1): ");
					input = Menu.s.nextLine();
					
					if (input.length() == 0) {
						c = 1;
						break;
					}
					
					try {
						c = Integer.parseInt(input);
						if (c < 0)
							throw new ChoiceOutOfRangeException();
						
						break;
						
					}
					
					catch (NumberFormatException | ChoiceOutOfRangeException e) {
						System.out.println("Expected a non-negative integer.");
					}
					
				}
				
				if (c != 0) {
					
					try {
						buyer.placeOrder(chosenItem, c);
					}
					
					catch (InsufficientStockException e) {
						System.out.println(e.toString());
					}
					
				}
				
				break;
			}
			
			else if (input.compareTo("n") == 0) {
				break;
			}
			
			else if (input.compareTo("back") == 0) {
				this.browseCategory(buyer, choice);
				return;
			}
			
			else {
				System.out.println("Expected y/n.");
			}
			
		}
	}


	private void ownerEditItem(Owner owner, Item chosenItem, String choice){
		String input;
		int newq;
		while (true){
			input = Menu.getUserInput("Enter new quantity: ");

			try {
				if (input.compareTo("back") == 0) {
					this.browseCategory(owner, choice);
					return;
				}
				
				newq = Integer.parseInt(input);
				if (newq <= 0) throw new ChoiceOutOfRangeException();
				break;

			} catch (NumberFormatException e) {

				System.out.println("Please insert a valid integer.");

			} catch (ChoiceOutOfRangeException e) {

				System.out.println(e.toString());

			}
			
		}
		
		try {
			this.eshop.updateItemStock(chosenItem, newq);
		}
		//this exception will never be thrown
		catch (ItemNotFoundException e) {}
	}

	private void ownerCheckStatus(Owner owner) {
		this.eshop.checkStatus();

		String input;
		int c;
		while (true){
			input = Menu.getUserInput("Select a buyer by number: ");

			try {
				if (input.toLowerCase().equals("back")) 
					return;
				c = Integer.parseInt(input);

				if (c <= 0){
					throw new ChoiceOutOfRangeException();
				}
				break;

			} catch (NumberFormatException e) {
				System.out.println("Please enter a valid integer.");
			} catch (ChoiceOutOfRangeException e){
				System.out.println(e.toString());
			}
		}

		this.ownerBuyerOptions(owner, this.eshop.getBuyersList().get(c-1), c);
	
	}

	private void ownerBuyerOptions(Owner owner, Buyer buyer, int c){
		try {
			buyer.getShoppingCart().showCart(buyer.getBuyerCategory());
		}
		catch (EmptyCartException e) {
			System.out.println(e.toString());
		}
		String input = Menu.getUserInput("Would you like to remove this buyer (y/n)? ").toLowerCase();
		if (input.equals("y")) {
			try {
				this.eshop.removeBuyer(buyer);
			}
			//this exception will never be thrown
			catch (BuyerNotFoundException e) {}
		} else if (input.equals("n")) {
			this.runLoop();
		} else if (input.equals("back")){
			this.ownerCheckStatus(owner);
		}
	}


	private void viewCart(Buyer buyer) {
		
		String input;		
		ShoppingCart cart = buyer.getShoppingCart();
		
		
		try {
			cart.showCart(buyer.getBuyerCategory());
		}
		
		catch (EmptyCartException e) {
			System.out.println(e.toString());
			return;
		}
		
		boolean validInput = false;
		
		do {
			
			input = Menu.getUserInput("Edit order, clear cart or checkout (edit, clear, checkout): ").toLowerCase();
			
			switch (input) {
			
				case "edit":
					this.editOrder(cart, buyer);
					validInput = true;
					break;
					
				case "clear":
					cart.clearCart();
					validInput = true;
					break;
					
				case "checkout":
					this.checkout(buyer);
					validInput = true;
					break;
				
				case "back":
					return;
				default:
					System.out.println("Expected edit, clear or checkout.");
			}
			
		} while (!validInput);
		
	}
	
	
	private void editOrder(ShoppingCart cart, Buyer buyer) {
		
		String input;
		
		Map<Item, Integer> allItems = cart.getOrderedItems();
		
		Item chosenItem = null;
		int quantity = 0;
		
		while (true) {
			
			int c;
			
			input = Menu.getUserInput("Choose a product by number (blank to exit): ");
			
			if (input.length() == 0)
				return;
			
			try {
				
				c = Integer.parseInt(input);
				
				Iterator<Item> iterator = allItems.keySet().iterator();
				
				int i = 1;
				
				while (iterator.hasNext()) {
					
					chosenItem = iterator.next();
					
					if (i == c)	{
						quantity = allItems.get(chosenItem);
						break;
					}
					
					++i;
					
				}
				
				if (quantity == 0)
					throw new ChoiceOutOfRangeException();
					
			}
			
			catch (NumberFormatException e) {
				System.out.println("Insert a valid product number.");
			}
			
			catch (ChoiceOutOfRangeException e) {
				System.out.println(e.toString());
			}
			
			break;
			
		}
		
		boolean validInput = false;
		
		do {
			
			input = Menu.getUserInput("Delete or edit order: ").toLowerCase();
			
			switch (input) {
			
				case "delete":
					
					try {
						cart.removeItem(chosenItem);
					}
					//this exception will never be thrown
					catch (ItemNotInCartException e) {}
					validInput = true;
					break;
					
				case "edit":
					
					int q;
					
					while (true) {
						
						input = Menu.getUserInput("New quantity: ");
						
						try {
							
							q = Integer.parseInt(input);
							
							if (q <= 0)
								throw new ChoiceOutOfRangeException();
							
							break;
							
						}
						
						catch (NumberFormatException e) {
							System.out.println("Expected a valid positive integer.");
						}
						
						catch (ChoiceOutOfRangeException e) {
							System.out.println(e.toString());
						}
					}
					
					try {
						cart.changeItemQuantity(chosenItem, q);
					}
					//this exception will never be thrown
					catch (ItemNotInCartException e) {}
					validInput = true;
					break;
					
				case "back":
					this.viewCart(buyer);
					return;
					
				default:
					System.out.println("Expected delete or edit.");
			
			}
			
			
		} while (!validInput);
		
	}
	
	private void checkout(Buyer buyer) {
		
		ShoppingCart cart = buyer.getShoppingCart();
		
		try {
			cart.checkout(buyer);
			System.out.println("Checked out successfully!");
		}
		catch (EmptyCartException e) {
			System.out.println(e.toString());
		}
		
	}
	
	public User getMail() {
		
		String input;
		User newUser;
		
		while (true) {
			
			input = getUserInput("E-mail address: ");
			
			this.m = p.matcher(input);
			
			if (m.find()) {
				
				try {
				
					newUser = this.eshop.authenticate(input);
				
				}
				
				catch (UserNotFoundException exc){
					
					String name;
					
					name = Menu.getUserInput("User name: ");
					
					newUser = new Buyer(name, input);
					
					try {
						this.eshop.addBuyer((Buyer) newUser);
					}
					//because of authenticate(), this exception will never be thrown
					catch (BuyerAlreadyExistsException e) {}
					
				}
				
				break;
				
			}
			
			else {
				System.out.println("Please enter a valid e-mail address!");
			}
			
		}
		
		return newUser;
		
	}
	
	public void runMenu() {
		this.commandsMap.clear();
		User user = getMail();
		if (user instanceof Owner) 	
			ownerMenu((Owner) user);
		else 
			buyerMenu((Buyer) user);
	}
	
	public void buyerMenu(Buyer buyer) {
		
		System.out.println("Welcome, " + buyer.getName() + "!");
		System.out.println("Your e-mail address is " + buyer.getMail());
		System.out.println("Current bonus points: " + buyer.getBonus());
		System.out.println("Current buyer category: " + buyer.getBuyerCategory());
		
		this.commandsMap.put("browse", () -> this.browse(buyer));
		this.commandsMap.put("view", () -> this.viewCart(buyer));
		this.commandsMap.put("checkout", () -> this.checkout(buyer));
		this.commandsMap.put("logout", () -> this.runMenu());
		this.commandsMap.put("exit", () -> System.exit(0));
		
		this.runLoop();
		
	}


	/*
	----------
	OWNER
	----------
	*/


	public void ownerMenu(Owner owner) {
		System.out.println("Welcome, " + owner.getName() + "!");
		System.out.println("Your e-mail address is " + owner.getMail());
		System.out.println("You are the owner of the shop.");

		this.commandsMap.put("browse", () -> this.browse(owner));
		this.commandsMap.put("status", () -> this.ownerCheckStatus(owner));
		this.commandsMap.put("logout", () -> this.runMenu());
		this.commandsMap.put("exit", () -> System.exit(0));

		this.runLoop();
	}
	
	/*
	//Implementation of custom Runnable function with argument
	
	abstract class RunnableCommand implements Runnable {
		
		Menu menu;
		
		public RunnableCommand(Menu menu) {
			
			this.menu = menu;
			
		}
		
	} */
	

}
