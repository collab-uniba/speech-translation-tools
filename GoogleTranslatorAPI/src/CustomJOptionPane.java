import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JTextField;


@SuppressWarnings("serial")
public class CustomJOptionPane extends JDialog implements ActionListener {

	private JOptionPane jOptionPane = null;
	private String textoInformado = null;
	private JTextField campoDeTexto = null;
	private JButton botaoSend = null;
	private JButton botaoCancelar = null;
	
	
	
	public CustomJOptionPane(String IdDoContatoDaConversa) {
		campoDeTexto = new JTextField(20);
		botaoSend = new JButton("Send");
		botaoCancelar = new JButton("Cancel");
		
		Object[] array = {botaoSend, botaoCancelar, campoDeTexto};
		
		jOptionPane = new JOptionPane(null, 
				                      JOptionPane.QUESTION_MESSAGE, 
				                      JOptionPane.OK_CANCEL_OPTION, 
				                      null,
				                      array, 
				                      null);
		this.setContentPane(jOptionPane);
		
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		
		/* Garante que o JTextField tera o focp inicial na janela. */
		addComponentListener(new ComponentAdapter() {
            @Override
            public void componentShown(ComponentEvent ce) {
            	campoDeTexto.requestFocusInWindow();
            }
        });
		
		campoDeTexto.addActionListener(this);
		botaoSend.addActionListener(this);
		botaoCancelar.addActionListener(this);
		
		pack();
	}
	
	public String getTextoInformado() {
		return this.textoInformado;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == botaoSend) {
			this.textoInformado = campoDeTexto.getText();
			System.out.println("Testando: " + campoDeTexto.getText());
		}
		
		if(e.getSource() == botaoCancelar) {
			this.textoInformado = "EXIT(0)_OPERATION";
		}
	}
}
