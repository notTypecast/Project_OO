
public abstract class Item {


    // variables

    private String name ;

    private double price ;

    private String description ;

    private int stock ;

    private int id ;

    
    public Item(String name,double price , String description , int stock , int id) throws IllegalCharacterException {
    	
    	
    	if(description.contains(";")) throw new IllegalCharacterException() ; 
    	
    	
        this.name = name ;
        this.price = price ;
        this.description = description ;
        this.stock = stock ;
        this.id = id ;
        
    }


    // methods

    
    public String getBasicInfo() {
        
        return this.name + ";" +  Double.toString(this.price) + ";" + this.description + ";" + Integer.toString(this.stock) + ";" +Integer.toString(this.id) ;
        
    }
    
    
    public abstract String getDetails();
    
    
    @Override
    public String toString() {
        
        String[] splited = getBasicInfo().split(";") ;
        
        return "Item name: "+ splited[0] + ", Price: " + splited[1] + ", Description: " + splited[2] + ", Stock: " + splited[3] + ", ID: " + splited[4] + getDetails() ;
         
    }
    
    
//--------------------------------------Setters-----------------------------------------------
    
    
    
    public void SetName(String n) {          //Name 
        
         this.name = n ;
         
    }
    
    public void setPrice(double p){         //Price
        
        this.price = p ;
        
    }
    
    public void setDescription(String d) {   //Description
        
        this.description = d ;
            
    }
    
    public void setStock(int s){             //Stock
        
        this.stock = s ; 
        
    }

    
    
    
    
//---------------------------------------Getters------------------------------------------------
    
    
    
    public String getName() {            //Name
        
        return this.name;
        
    }
    
    public double getPrice() {  		//Price
        
        return this.price ;
        
    }
    
    public int getStock() {				//stock
        
        return this.stock ;
        
    }
    
    public int getId() {				//Id
        
        return this.id ;
        
    }

    
    
}
