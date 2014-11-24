import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JDialog;
import javax.swing.JOptionPane;


public class CustomJOptionPane extends JDialog implements ActionListener {

	private JOptionPane jOptionPane = null;
	private String textoInformado = null;
	
	public CustomJOptionPane(String IdDoContatoDaConversa) {
		
	}
	
	public String getTextoInformado() {
		return this.textoInformado;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}
}
