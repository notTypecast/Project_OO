import java.util.ArrayList;
import java.util.List;

public class EShop {

    // instance variables

    private String name;
    private Owner owner;
    private ArrayList<Item> itemsList = new ArrayList<Item>();
    private ArrayList<Buyer> buyersList = new ArrayList<Buyer>();

    // constructors 

    public EShop(String name, Owner owner) {
        this.name = name;
        this.owner = owner;
    }

    // methods
    // throws exception if the item already exists in the shop
    public void addItem(Item i) throws ItemAlreadyExistsException{

        if (this.itemsList.contains(i)){
            throw new ItemAlreadyExistsException();
        }

        itemsList.add(i);
        System.out.println("Item successfully added.");
    }


    public Item getItemById(int id) throws ItemNotFoundException{

        for (Item i: this.itemsList){
            if (i.getId() == id) return i;
        }

        // this will not be executed if item is found
        throw new ItemNotFoundException();

    }

    public void removeItem(Item i) throws ItemNotFoundException{

        // creating a temporary Item reference, will be used to remove an item
        Item tempItemRef = null;

        for (Item iref: this.itemsList){
            if (iref.getId() == i.getId()){
                // copying the reference, since removing now will cause ConcurrentModificationException
                tempItemRef = i;
            }
        }

       try {
           // this is a dummy method call to determine if item was found
           // will throw NullPointerException only if the item was not found
           tempItemRef.getId();

           // this will not be executed if item is not found
           this.itemsList.remove(tempItemRef);

       } catch (NullPointerException e){
            throw new ItemNotFoundException();
       }
    }

    public void addBuyer(Buyer b) throws BuyerAlreadyExistsException{
        if (this.buyersList.contains(b)){
            throw new BuyerAlreadyExistsException();
        }

        buyersList.add(b);
        System.out.println("Buyer successfully added.");
    }

    public void removeBuyer(Buyer b) throws BuyerNotFoundException{
        // creating a temporary Buyer reference, will be used to remove an item
        Buyer tempBRef = null;

        for (Buyer bref: this.buyersList){

            // treating the buyer's email as primary key
            // will use that to identify the buyer to be removed
            if ( bref.getMail().equals(b.getMail()) ){
                // copying the reference, since removing now will cause ConcurrentModificationException
                tempBRef = b;
            }
        }

       try {
           // this is a dummy method call to determine if buyer was found
           // will throw NullPointerException only if the buyer was not found
           tempBRef.getMail();

           // this will not be executed if buyer is not found
           this.buyersList.remove(tempBRef);
           tempBRef.getShoppingCart().clearCart();

       } catch (NullPointerException e){
            throw new BuyerNotFoundException();
       }
    }

    public void updateItemStock(Item item, int stock) throws ItemNotFoundException{
        
        if (!this.itemsList.contains(item)){
            throw new ItemNotFoundException();
        }

        item.setStock(stock);
        System.out.println("Successfully updated stock of item with id " + item.getId() + ".");

    }


    public void showCategories(){
        System.out.println("------");
        System.out.println("Available categories: ");
        for (String str: this.getCategories()){
            System.out.println(str.substring(0, 1).toUpperCase() + str.substring(1));
        }

        System.out.println("------");

    }

    public void showProductsInCategory(String category){

        System.out.println("------");
        System.out.println("Showing available items in category: " + category);

        

        // using toLowerCase to make the comparison case insensitive
        for (Item iref: this.itemsList){
            if ( (iref.getClass().getSimpleName().toLowerCase()).equals(category.toLowerCase()) ) {
                System.out.println(iref.toString());
            }
        }


        System.out.println("------");
    }

    public void showProduct(Item product){
        System.out.println(product.toString());
    }

    public void checkStatus(){
        System.out.println("-------------");
        int count = 1;
        for (Buyer bref: buyersList){
            System.out.println(count++ + "\t" + bref.getName() + "\t" + bref.getBonus() + "\t" + bref.getBuyerCategory());
        }
        

        System.out.println("-------------");

    }

    public User authenticate(String mail) throws UserNotFoundException{
        
        if (mail.equals(this.owner.getMail())){
            return this.owner;
        } else {
            for (Buyer bref: this.buyersList){
                if (bref.getMail().equals(mail)) {
                    return bref;
                }
            }
        }

        // this will not be executed if user is found
        throw new UserNotFoundException();

    }

    String getName(){
        return this.name;
    }

    List<String> getCategories(){

        // the category names are the names of Item subclasses

        ArrayList<String> tempList = new ArrayList<String>();

        for (Item iref: this.itemsList){

            // ensuring the list has no duplicate categories
            if (!tempList.contains(iref.getClass().getSimpleName())) {
                tempList.add(iref.getClass().getSimpleName().toLowerCase());
            }
        }

        return tempList;

    }

    List<Buyer> getBuyersList(){
        return this.buyersList;
    }
}
