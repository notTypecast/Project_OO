
public class Owner extends User {
	
	private boolean isAdmin;
	
	public Owner(String name, String mail) {
		super(name, mail);
		this.isAdmin = true;
	}
	
	//getter for admin status
	public boolean getAdminStatus() {
		return this.isAdmin;
	}
	
	//change admin status to opposite value
	public void changeAdminStatus() {
		this.isAdmin = this.isAdmin ? false : true;
	}

}
