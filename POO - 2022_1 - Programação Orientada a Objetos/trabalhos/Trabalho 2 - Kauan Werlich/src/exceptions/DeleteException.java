package exceptions;

public class DeleteException extends Exception {
	
	public DeleteException () {
		
	}
	
	public DeleteException (String mensagem) {
		super (mensagem);
	}
}
