
public class Paper extends Item{

    
    Paper(String name,double price , String description , int stock , int id){

        super(name , price , description , stock , id);

    }

    //Variables

    private int weight ;

    private int pages ;

//---------------getDetails implementation------------------

    public String getDetails(){

        return ", Paper weight " + Integer.toString(weight) + "g " + ", Pages of paper : " + Integer.toString(pages);

    }


//-----------------------Setters----------------------------

    public void setWeight(int w){       //weight

        this.weight = w ;

    }


    public void setPages(int p){

        this.pages = p ;

    }

//--------------------------------Getters---------------------


    public int getWeight(){

        return this.weight ;

    }

    public int getPages(){

        return this.pages ;

    }



}
