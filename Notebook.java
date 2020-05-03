
public class Notebook extends Item{

    //Variables

    private int sections ;
    
    
    
    Notebook(String name,double price , String description , int stock , int id,int sections) throws IllegalCharacterException{

        super(name , price , description , stock , id);     //calls Item constructor
        
        this.sections = sections ;

    }



    //Methods

//-----------------getDetails implementation-----------------

    public String getDetails(){

        return ", Sections: " + Integer.toString(sections);

    }


//-------------------Setters-----------------------------------


    public void setSections(int s){

        this.sections = s ;

    }


//----------------Getters--------------------------------------

    public int getSections(){

        return this.sections ;

    }


}
