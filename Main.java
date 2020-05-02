

public class Main {

	public static void main(String[] args) {
		
		
		EShop eshop = new EShop("test_shop",new Owner("test","test@mail.gr"));
		
		Item[] item = new Item[12];
		
		Buyer[] buyers = new Buyer[3];
		
		try {
			item[0] = new Pen("pen1", 10.5 ,"apple pen",100 , 12 ,"red",10.76) ;
			
			item[1] = new Pen("pen2", 12 , "pineapple pen" , 14 , 123 , "blue" , 10);
			
			item[2] = new Pen("pen3", 17 , "Pen pineapple apple pen " , 120 , 200 , "brown" , 14);
			
			item[3] = new Pencil("Pencil1", 10.5 , "Pencil 1" , 100 , 56 , 12.5 , Pencil.PENCIL_TYPE.H );
			
			item[4] = new Pencil("Pencil2", 13.5 , "Pencil 2" , 140 , 356 , 12.7 , Pencil.PENCIL_TYPE.HB );
			
			item[5] = new Pencil("Pencil3", 0.5 , "Pencil 3" , 196 , 66 , 1.5 , Pencil.PENCIL_TYPE.B );
			
			item[6] = new Notebook("notebook1", 4 , "notebook 1" , 100 , 162 , 3);
			
			item[7] = new Notebook("notebook2", 6 , "notebook 2" , 254 , 54 , 2);
			
			item[8] = new Notebook("notebook3", 2 , "notebook 3" , 653 , 98 , 5);
			
			item[9] = new Paper("Paper1", 3 , "Paper 1" , 67 , 9898 , 1223 , 85);
			
			item[10] = new Paper("Paper2", 5 , "Paper 2" , 63 , 98943 , 1054 , 66);
			
			item[11] = new Paper("Paper3", 9 , "Paper 3" , 623 , 912 , 1621 , 55);
		}
		catch(IllegalCharacterException e2) {}
		
		
		buyers[0] = new Buyer("nick", "nick@mail.com");
		
		buyers[1] = new Buyer("chris" , "chris@mail.com");
		
		buyers[2] = new Buyer("george" , "george@mail.com");
		
		
		for(Item i : item) {
			
			try {
				
				eshop.addItem(i);
			}
			catch(ItemAlreadyExistsException e) {}
			
		}
		
		
		for(Buyer b : buyers) {
			
			try {
				
				eshop.addBuyer(b);
				
			}
			catch(BuyerAlreadyExistsException ex) {}
			
		}
		
		try {
			
			buyers[0].placeOrder(item[1], 4);
			
			buyers[0].placeOrder(item[4], 2);
			
			buyers[0].placeOrder(item[8],3);
			
			buyers[1].placeOrder(item[3], 2);
			
			buyers[1].placeOrder(item[10], 1);
			
			buyers[1].placeOrder(item[9], 2);
			
			buyers[2].placeOrder(item[2], 1);
			
			buyers[2].placeOrder(item[6], 3);
			
			buyers[2].placeOrder(item[11], 5);
			
			
		}
		catch(InsufficientStockException e1) {}
		
		
		Menu menu = new Menu(eshop);
		
		menu.runMenu();
		
		
		
		
		
	}

}
