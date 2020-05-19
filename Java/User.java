
public abstract class User {
	
	private String name;
	private String mail;
	
	public User(String n, String m) throws InvalidNameLengthException {
		if ((n.length() > 2) && (n.length() < 20))
			this.name = n;
		else
			throw new InvalidNameLengthException();
			
		this.mail = m;
	}
	
	//getter for name
	public String getName() {
		return this.name;		
	}
	
	//setter for name
	public void setName(String n) {
		this.name = n;
	}
	
	//getter for mail
	public String getMail() {
		return this.mail;
	}
	
	//setter for mail
	public void setMail(String m) {
		this.mail = m;
	}

}
