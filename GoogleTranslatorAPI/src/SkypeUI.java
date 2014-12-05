import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.ListModel;

import javax.swing.WindowConstants;
import javax.swing.border.BevelBorder;
import javax.swing.SwingUtilities;

import com.google.api.GoogleAPI;
import com.google.api.translate.Language;
import com.google.api.translate.TranslateV2;
import com.skype.Chat;
import com.skype.ChatMessage;
import com.skype.ChatMessageListener;
import com.skype.Skype;
import com.skype.SkypeException;
import com.skype.connector.Connector;
import com.skype.connector.ConnectorException;

@SuppressWarnings("unused")
public class SkypeUI extends javax.swing.JFrame implements ActionListener, MouseListener {

	{
		//Set Look & Feel
		try {
			javax.swing.UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	private static final long serialVersionUID = 1L;
	private JPanel painelListaDeAmigos;
	
	@SuppressWarnings("rawtypes")
	private JList listaDeAmigos;
	
	private JLabel labelFriendsList;
	private JScrollPane scrollPane;
	
	private JMenuBar menuBar;

	private JMenu menuTranslator;
	private JMenu menuHelp;

	private JMenuItem menuItemAbout;
	private JMenuItem menuItemSair;
	private JMenuItem menuItemHistory;
	
	private JTabbedPane jTabbedPane1;
	private JTabbedPane painelTabs;
	private JPanel painelPrincipal;
	private JTabbedPane jTabbedPane2;

	private Chat chat = null;
	
	/**
	* Auto-generated main method to display this JFrame
	*/
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				SkypeUI inst = new SkypeUI();
				inst.setLocationRelativeTo(null);
				inst.setVisible(true);
			}
		});
	}
	
	public SkypeUI() {
		super();
		initGUI();
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	private void initGUI() {
		try {
			setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
			getContentPane().setLayout(null);
			this.setResizable(false);
			{
				menuBar = new JMenuBar();
				setJMenuBar(menuBar);
				{
					menuTranslator = new JMenu();
					menuBar.add(menuTranslator);
					menuTranslator.setText("Translator");
					{
						menuItemHistory = new JMenuItem();
						menuTranslator.add(menuItemHistory);
						menuItemHistory.setText("History");
					}
					{
						menuItemSair = new JMenuItem();
						menuTranslator.add(menuItemSair);
						menuItemSair.setText("Exit");
						menuItemSair.addActionListener(this);
					}
				}
				{
					menuHelp = new JMenu();
					menuBar.add(menuHelp);
					menuHelp.setText("Help");
					{
						menuItemAbout = new JMenuItem();
						menuHelp.add(menuItemAbout);
						menuItemAbout.setText("About");
					}
				}
			}
			{
				painelListaDeAmigos = new JPanel();
				getContentPane().add(painelListaDeAmigos, "Center");
				painelListaDeAmigos.setBounds(481, 6, 193, 423);
				painelListaDeAmigos.setLayout(null);
				painelListaDeAmigos.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
				painelListaDeAmigos.setSize(194, 423);
				{
					labelFriendsList = new JLabel();
					painelListaDeAmigos.add(labelFriendsList);
					labelFriendsList.setText("Contact List");
					labelFriendsList.setBounds(58, 9, 80, 17);
					labelFriendsList.setFont(new java.awt.Font("Baskerville Old Face",0,16));
				}
				{
					scrollPane = new JScrollPane();
					painelListaDeAmigos.add(scrollPane);
					scrollPane.setBounds(2, 31, 189, 389);
					{
						
						/* Criando a lista de amigos e setando no JList */
						FriendsList friendsList = new FriendsList();
						Vector<String> listaFinal = friendsList.getFriendsIdsAsString();
						ListModel listaDeAmigosModel = new DefaultComboBoxModel(listaFinal);
						
						listaDeAmigos = new JList();
						scrollPane.setViewportView(listaDeAmigos);
						listaDeAmigos.setModel(listaDeAmigosModel);
						listaDeAmigos.setBounds(184, 14, 155, 444);
						listaDeAmigos.addMouseListener(this);
					}
				}
			}
			{
				painelPrincipal = new JPanel();
				getContentPane().add(painelPrincipal);
				painelPrincipal.setLayout(null);
				painelPrincipal.setBounds(7, 6, 468, 413);
				painelPrincipal.setBorder(BorderFactory.createEtchedBorder(BevelBorder.LOWERED));
				painelPrincipal.setSize(468, 423);
				{
					painelTabs = new JTabbedPane();
					painelPrincipal.add(painelTabs);
					painelTabs.setBounds(7, 6, 454, 221);
					{
						jTabbedPane1 = new JTabbedPane();
						painelTabs.addTab("jTabbedPane1", null, jTabbedPane1, null);
						jTabbedPane1.setPreferredSize(new java.awt.Dimension(316, 237));
					}
					{
						jTabbedPane2 = new JTabbedPane();
						painelTabs.addTab("jTabbedPane2", null, jTabbedPane2, null);
					}
				}
			}
			pack();
			this.setSize(686, 485);
		} catch (Exception e) {
		    //add your error handling code here
			e.printStackTrace();
		}
	}

	
	
	/* The methods below are used to connect
	 * to skype communication layer. */
	/*static {
		Connector.useJNIConnector(true);
	}
	
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
		/*try {
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
	};*/
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		
		if(arg0.getSource() == menuItemSair) {
			System.exit(0);
		}
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		
		if(arg0.getClickCount() == 2) {
			
			String idDoContato = (String) listaDeAmigos.getSelectedValue();
			String texto = "";	
			
			//connect();
			//CustomJOptionPane customJOptionPane = new CustomJOptionPane(idDoContato);
			//customJOptionPane.setVisible(true);
			//JFrame aux = new JFrame();
			//JWindowChat jWindowChat = new JWindowChat();
			//jWindowChat.criaJanela(idDoContato);
			//texto = jWindowChat.getTexto();
			
			JWindowChat jWindowChat = new JWindowChat(idDoContato);
			jWindowChat.setVisible(true);
				
			//while (texto != null && !texto.equals("EXIT(0)_OPERATION")) {
				// String saida = v2.execute(texto, Language.PORTUGUESE, Language.ENGLISH);

				//texto = jWindowChat.getTextoInformado();
				//texto = JOptionPane.showInputDialog("Digite a mensagem para enviar...");
					
					
				//sendMessage(idDoContato, texto);
					
			//}
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
