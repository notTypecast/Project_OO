
public class Pencil extends Item {


	Pencil(String name,double price , String description , int stock , int id){

		super(name , price ,description , stock , id);  	//calls Item constructor

	}


    //Variables
	
	private double tipSize;
	
	private enum PENCIL_TYPE {
		
		H,B,HB ; 
		
	}

	private PENCIL_TYPE pencilType ;


	//Methods
	
//---------------------getDetails implementation-------------------------
	
	public String getDetails() {
		
	
		return ", Pencil Type is : " + pencilType.toString() +", Pencil tip Size is : " + Double.toString(tipSize) ;
		
	}
	
	
//--------------------------Setters--------------------------------------
	
	
	public void setPencilType(PENCIL_TYPE size) {  // pencil type
		
		this.pencilType = size ;
		
	}

	public void setTipSize(double size){   		//tip size

		this.tipSize = size ;

	}
	
	
//-------------------------Getters---------------------------------------
	
	
	public double getTipSize() {    				//tip size
		
		return tipSize ;
		
	}

	public PENCIL_TYPE getPencilType() {		//pencil type

		return this.pencilType ;
		
    }
    
}
