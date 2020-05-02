
public class Pen extends Item{


	Pen(String name,double price , String description , int stock , int id){
		
		super(name,price , description , stock ,id);  	//calls Item constructor
		
	} 


	//variables 

    private String color ;
	
	private double tipSize ;


	
	//methods

//----------------getDetails implementation---------
	
	
	public String getDetails() {
		
		return ", Color of Pen is : " + this.color + ", Pen's tip is : " + Double.toString(tipSize) + " mm";
				
	}
	
	
//---------------Setters-----------------------------
	
	
	public void setColor(String c) {    	//color
		
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
