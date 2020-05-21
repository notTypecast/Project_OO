import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Menu {
	
	//Scanner for System.in
	public static Scanner s = new Scanner(System.in);
	
	//Regular expression for validating given email addresses
	private String regex_pattern = "^([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$";
	private Pattern p;
	private Matcher m;
	
	//Map mapping commands to functions
	//Is LinkedHashMap so commands retain their place order
	private LinkedHashMap<String, Runnable> commandsMap;
	
	private EShop eshop;
	
	public Menu(EShop eshop) {
		this.eshop = eshop;
		
		this.p = Pattern.compile(this.regex_pattern);
		this.commandsMap = new LinkedHashMap<String, Runnable>();
	}
	
	//static method to get input from user
	public static String getUserInput(String outputMsg) {
		
		String input;	
		System.out.print(outputMsg);
		input = Menu.s.nextLine();
		return input.trim();
		
	}
	
	//method to run command loop
	private void runLoop() {
		
		String command;
		
		while (true) {
			
			//get a new command
			command = getUserInput(">> ");
			boolean foundCommand = false;
			
			//loop through commandsMap
			for (Map.Entry<String, Runnable> entry: this.commandsMap.entrySet()) {
				
				//if command is in commandMap
				if (command.compareTo(entry.getKey()) == 0) {
					
					//run the function mapped to that command
					entry.getValue().run();
					foundCommand = true;
					
				}
			}
			
			//if no function was run
			if (!foundCommand) {
				
				//if command was the help command, show all available commands
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
	
	
	//browse the E-Shop
	private void browse(User user) {
		
		//show shop information
		System.out.println("Shop name: " + this.eshop.getName());
		this.eshop.showCategories();
		
		//get all the eshop categories
		List<String> categories = this.eshop.getCategories();
		
		String choice;
		
		while (true) {
			choice = Menu.getUserInput("Choose a category: ").toLowerCase();
			try {
				
				//move on if category was chosen
				if (categories.contains(choice)) {
					break;
				}
				//if back was chosen, exit method
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
		
		//show information for one category
		this.eshop.showProductsInCategory(choice);
		
		Item chosenItem;
		
		//get a specific item (by ID)
		while (true) {
			input = Menu.getUserInput("Item ID: ");
			
			try {
				
				//for back, run the previous function "browse" and exit this one afterwards
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
		
		
		//run different function based on whether the user is an owner or not
		if (user instanceof Buyer) {
			buyerPlaceOrder((Buyer) user, chosenItem, choice);
		} else {
			ownerEditItem((Owner) user, chosenItem, choice);
		}
		
	}
	
	//method for placing an order as a buyer
	private void buyerPlaceOrder(Buyer buyer, Item chosenItem, String choice) {
		String input;
		int c;
		
		//confirm whether the user wants to place the order
		while (true) {
			
			System.out.print("Would you like to place an order for this item (y/n)? ");
			input = Menu.s.nextLine().toLowerCase();
			
			if (input.compareTo("y") == 0) {
				
				//if they do, ask for a quantity
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
					
					//try to place the order
					try {
						buyer.placeOrder(chosenItem, c);
					}
					
					//if there isn't enough stock, inform the user
					catch (InsufficientStockException e) {
						System.out.println(e.toString());
					}
					
				}
				
				break;
			}
			
			else if (input.compareTo("n") == 0) {
				break;
			}
			
			//if the user chose to go back, go the the previous function "browseCategory"
			//and exit this function (so the loop doesn't keep running after browseCategory finishes)
			else if (input.compareTo("back") == 0) {
				this.browseCategory(buyer, choice);
				return;
			}
			
			else {
				System.out.println("Expected y/n.");
			}
			
		}
	}

	//method for the owner to edit the quantity of an item
	private void ownerEditItem(Owner owner, Item chosenItem, String choice){
		String input;
		int newq;
		//get a new quantity
		while (true){
			input = Menu.getUserInput("Enter new quantity: ");

			try {
				//call the previous "browseCategory" function and exit this one on "back"
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
		
		//update the item stock
		try {
			this.eshop.updateItemStock(chosenItem, newq);
		}
		//this exception will never be thrown because the item was chosen
		//out of a list of items, and defensive programming was employed
		catch (ItemNotFoundException e) {}
	}

	
	//method for owner to check eshop status
	private void ownerCheckStatus(Owner owner) {
		//show buyers, numbered
		this.eshop.checkStatus();

		String input;
		int c;
		
		//select a specific buyer number
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

		//run ownerBuyerOptions for the chosen buyer
		try {
			this.ownerBuyerOptions(owner, this.eshop.getBuyersList().get(c-1), c);
		}
		catch (IndexOutOfBoundsException exc) {
			System.out.println("No buyer has that number!");
		}
	
	}

	
	//method for owner to be able to remove buyers from the eshop
	private void ownerBuyerOptions(Owner owner, Buyer buyer, int c){
		
		//show buyer information
		try {
			buyer.getShoppingCart().showCart(buyer.getBuyerCategory());
		}
		catch (EmptyCartException e) {
			System.out.println(e.toString());
		}
		//ask for confirmation to remove given buyer
		while (true) {
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
			} else {
				//if incorrect data was given, go back to the start of the loop
				System.out.println("Expected y/n.");
				continue;
			}
			
			break;
		}
	}

	//method to show a buyer their cart
	private void viewCart(Buyer buyer) {
		
		//get the cart object
		String input;		
		ShoppingCart cart = buyer.getShoppingCart();
		
		//show the cart
		try {
			cart.showCart(buyer.getBuyerCategory());
		}
		
		catch (EmptyCartException e) {
			System.out.println(e.toString());
			return;
		}
		
		boolean validInput = false;
		
		//ask for whether they want to edit an order, clear the cart, or check out
		//run the respective methods for each option
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
	
	//method for buyers to be able to edit their orders
	private void editOrder(ShoppingCart cart, Buyer buyer) {
		
		String input;
		
		//get all the items the buyer has ordered
		Map<Item, Integer> allItems = cart.getOrderedItems();
		
		Item chosenItem = null;
		int quantity = 0;
		
		//get the user's order choice
		while (true) {
			
			int c;
			
			input = Menu.getUserInput("Choose a product by number (blank to exit): ");
			
			if (input.length() == 0)
				return;
			
			try {
				
				c = Integer.parseInt(input);
				
				//Use an iterator to iterate through the set of the keys (which are the items)
				Iterator<Item> iterator = allItems.keySet().iterator();
				
				int i = 1;
				//iterate through each item				
				while (iterator.hasNext()) {

					chosenItem = iterator.next();
					//if the current item number matches the given number
					if (i == c)	{
						//get the quantity for the item and break
						quantity = allItems.get(chosenItem);
						break;
					}
					
					++i;
					
				}
				
				//if the quantity is still 0, item number given was wrong
				if (quantity == 0)
					throw new ChoiceOutOfRangeException();
				//if the quantity isn't 0, then an item was found, so break
				else
					break;
					
			}
			
			catch (NumberFormatException e) {
				System.out.println("Insert a valid product number.");
			}
			
			catch (ChoiceOutOfRangeException e) {
				System.out.println(e.toString());
			}
			
		}
		
		boolean validInput = false;
		
		//ask the user if they'd like to delete or edit the chosen order
		//and run the respective functions
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
					catch (InsufficientStockException e) {
						System.out.println(e.toString());
						continue;
					}
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
	
	//method for user to be able to check out
	private void checkout(Buyer buyer) {
		
		ShoppingCart cart = buyer.getShoppingCart();
		
		//run the checkout function
		try {
			//the checkout function asks for confirmation, so it is not needed here
			cart.checkout(buyer);
		}
		//if the exception is raised, the cart is empty
		catch (EmptyCartException e) {
			System.out.println(e.toString());
		}
		
	}
	
	//method to get mail from the user
	public User getMail() {
		
		String input;
		User newUser;
		
		//ask the user for an email address
		while (true) {
			
			input = getUserInput("E-mail address: ");
			
			//try to match the regular expression for mails
			this.m = p.matcher(input);
			
			//if the regular expression matches, a valid mail was given
			if (m.find()) {
				
				//authenticate the user with the given mail
				//returns the user, if found
				try {
				
					newUser = this.eshop.authenticate(input);
				
				}
				
				//if the user was not found, create a new user and add them
				catch (UserNotFoundException exc){
					
					String name;
					
					while (true){
						try {
							name = Menu.getUserInput("User name: ");
					
							newUser = new Buyer(name, input);
							break;
						} catch(InvalidNameLengthException e){
							System.out.println(e.toString());
						}
					}
					
					try {
						
						this.eshop.addBuyer((Buyer) newUser);
					}
					//this exception will never be thrown
					//because to reach this point, UserNotFoundException has been thrown
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
	
	//First method to be run
	//gets a new mail and determines if the user exists and is an owner or a buyer
	public void runMenu() {
		this.commandsMap.clear();
		User user = getMail();
		if (user instanceof Owner) 	
			ownerMenu((Owner) user);
		else 
			buyerMenu((Buyer) user);
	}
	
	//Buyer menu method
	public void buyerMenu(Buyer buyer) {
		
		//output information about the buyer
		System.out.println("Welcome, " + buyer.getName() + "!");
		System.out.println("Your e-mail address is " + buyer.getMail());
		System.out.println("Current bonus points: " + buyer.getBonus());
		System.out.println("Current buyer category: " + buyer.getBuyerCategory());
		
		//Add buyer commands to the command map, mapping them to lambdas of pre-existing methods
		this.commandsMap.put("browse", () -> this.browse(buyer));
		this.commandsMap.put("view", () -> this.viewCart(buyer));
		this.commandsMap.put("checkout", () -> this.checkout(buyer));
		this.commandsMap.put("logout", () -> this.runMenu());
		this.commandsMap.put("exit", () -> System.exit(0));
		
		//run the loop which gets the commands from user
		this.runLoop();
		
	}


	//same as buyerMenu, but for owner commands
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
