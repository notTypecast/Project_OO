
public class Pen extends Item{


	


	//variables 

    private String color ;
	
	private double tipSize ;
	
	
	Pen(String name,double price , String description , int stock , int id,String color , double tipSize) throws IllegalCharacterException{
		
		super(name,price , description , stock ,id);  	//calls Item constructor
		
		if (color.contains(";"))
			throw new IllegalCharacterException();
		
		this.color = color ;
		
		this.tipSize = tipSize ;
		
	} 


	
	//methods

//----------------getDetails implementation---------
	
	
	public String getDetails() {
		
		return ", Color: " + this.color + ", Tip: " + Double.toString(tipSize) + " mm";
				
	}
	
	
//---------------Setters-----------------------------
	
	
	public void setColor(String c) throws IllegalCharacterException {    	//color
		
		if (c.contains(";"))
			throw new IllegalCharacterException();
		
		this.color = c ;
		
	}
	
	public void SetTipSize(double size) {		//TipSize
		
		this.tipSize = size ;
		
	}
	

//------------Getters-----------------------------
	
	
	public String getColor() {		//Color
		
		return this.color ;
		
	}
	
	public double getTipSize() {		//TipSize
		
		return this.tipSize ;
		
	}

}
