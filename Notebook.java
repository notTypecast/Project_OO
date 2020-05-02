
public class Notebook extends Item{

    
    Notebook(String name,double price , String description , int stock , int id){

        super(name , price , description , stock , id);     //calls Item constructor

    }


    //Variables

    private int sections ;



    //Methods

//-----------------getDetails implementation-----------------

    public String getDetails(){

        return ", Sections are : " + Integer.toString(sections) ;

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
