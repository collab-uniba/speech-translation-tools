
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;

import com.skype.Chat;
import com.skype.ChatMessage;
import com.skype.ChatMessageListener;
import com.skype.Skype;
import com.skype.SkypeException;
import com.skype.connector.Connector;
import com.skype.connector.ConnectorException;

@SuppressWarnings("serial")
public class JWindowChat extends javax.swing.JDialog implements KeyListener, ActionListener {
	private JButton botaoSend;
	private JTextArea areaDeTexto;
	private JTextArea textAreaUserInput;
	private JScrollPane scrollPaneUserInput;
	private JScrollPane scrollPane;
	
	private String idDoContato = "";
	
	private String textoEnviando = "";
	
	private Chat chat = null;
	
	static {
		Connector.useJNIConnector(true);
	}

	public void criaJanela(String idDoContato) {
		JFrame frame = new JFrame();
		JWindowChat inst = new JWindowChat(frame);
		inst.setVisible(true);
		this.idDoContato = idDoContato;
		inst.setTitle(this.idDoContato);
	}

	public JWindowChat(JFrame frame) {
		super(frame);
		initGUI();

	}
	
	public JWindowChat(){}

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
			
			try {
				connect();
				
				if(idDoContato != null && !idDoContato.equals("")) {
					sendMessage(idDoContato, textoEnviando);
				}
				
				
			} catch (Exception e) {
				
				e.printStackTrace();
			}
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
	
	/* The methods below are used to connect
	 * to skype communication layer. */
	
	
	public void sendMessage(String id, String text) throws SkypeException {
		chat = (null == chat ? Skype.chat(id) : chat);
		chat.send(text);
	}

	public void connect() throws Exception {
		Connector.Status status = null;
		Connector conn = Connector.getInstance();

		try {
			status = conn.connect();
		} catch (ConnectorException e1) {
			e1.printStackTrace();
			throw new Exception(e1.getMessage());
		}

		if (status != Connector.Status.ATTACHED)
			throw new Exception(new Exception(
					"Please install Skype from www.skype.com and run it."));

		/* Add Skype4Java listeners. */
		try {
			Skype.addChatMessageListener(chatMessageListener);
		} catch (SkypeException e) {
			e.printStackTrace();
		}

		System.out.println("Connected, Skype ver. " + Skype.getVersion());
	}

	private ChatMessageListener chatMessageListener = new ChatMessageListener() {

		@Override
		public void chatMessageSent(ChatMessage arg0) throws SkypeException {
		}

		@Override
		public void chatMessageReceived(ChatMessage chatMessage)
				throws SkypeException {
			System.out.println(chatMessage.getSenderDisplayName() + "("
					+ chatMessage.getSenderId() + "): "
					+ chatMessage.getContent());
		}
	};
}
