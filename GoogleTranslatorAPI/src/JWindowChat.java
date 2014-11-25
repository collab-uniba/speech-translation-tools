
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;

@SuppressWarnings("serial")
public class JWindowChat extends javax.swing.JDialog implements KeyListener, ActionListener {
	private JButton botaoSend;
	private JTextArea areaDeTexto;
	private JTextArea textAreaUserInput;
	private JScrollPane scrollPaneUserInput;
	private JScrollPane scrollPane;
	
	private String textoEnviando = "";

	public void criaJanela() {
		JFrame frame = new JFrame();
		JWindowChat inst = new JWindowChat(frame);
		inst.setVisible(true);
	}

	public JWindowChat(JFrame frame) {
		super(frame);
		initGUI();
	}

	private void initGUI() {
		try {
			{
				getContentPane().setLayout(null);
			}
			{
				botaoSend = new JButton();
				getContentPane().add(botaoSend);
				botaoSend.setText("Send...");
				botaoSend.setBounds(450, 333, 80, 28);
				botaoSend.addKeyListener(this);
				botaoSend.addActionListener(this);
			}
			{
				scrollPane = new JScrollPane();
				getContentPane().add(scrollPane);
				scrollPane.setBounds(6, 6, 524, 286);
				scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

				{
					areaDeTexto = new JTextArea();
					scrollPane.setViewportView(areaDeTexto);

					/* Wraps the text and the end of the text area. */
					areaDeTexto.setLineWrap(true);		
					areaDeTexto.setEditable(false);
				}
			}
			{
				scrollPaneUserInput = new JScrollPane();
				getContentPane().add(scrollPaneUserInput);
				scrollPaneUserInput.setBounds(6, 298, 438, 63);
				{
					textAreaUserInput = new JTextArea();
					scrollPaneUserInput.setViewportView(textAreaUserInput);
					scrollPaneUserInput.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
					textAreaUserInput.setLineWrap(true);
					textAreaUserInput.addKeyListener(this);
					textAreaUserInput.setFocusable(true);

					textAreaUserInput.grabFocus();
					textAreaUserInput.requestFocus();
					textAreaUserInput.setEnabled(true);
				}
			}
			this.setSize(552, 406);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(arg0.getSource() == botaoSend) {

			if(areaDeTexto.getText().equals("")) {
				areaDeTexto.setText(textAreaUserInput.getText());
			} else {
				areaDeTexto.append("\n" + textAreaUserInput.getText());
			}
			textoEnviando = textAreaUserInput.getText();
			textAreaUserInput.setText("");
		}
	}

	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyReleased(KeyEvent e) {

		if(e.getKeyCode() == KeyEvent.VK_ENTER) {
			System.out.println(areaDeTexto.getText());
		}
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub

	}
	
	public String getTexto() {
		return textAreaUserInput.getText() != null ? textAreaUserInput.getText() : "";
	}
}
