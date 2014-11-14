import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;
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

import com.skype.Chat;


/**
* This code was edited or generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a corporation,
* company or business for any purpose whatever) then you
* should purchase a license for each developer using Jigloo.
* Please visit www.cloudgarden.com for details.
* Use of Jigloo implies acceptance of these licensing terms.
* A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED FOR
* THIS MACHINE, SO JIGLOO OR THIS CODE CANNOT BE USED
* LEGALLY FOR ANY CORPORATE OR COMMERCIAL PURPOSE.
*/
public class SkypeUI extends javax.swing.JFrame implements ActionListener {

	{
		//Set Look & Feel
		try {
			javax.swing.UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * 
	 */
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
						FriendsList friendsList = new FriendsList();
						//int numeroAmigos = friendsList.getNumberOfFriends();
						
						//String listaDeAmigos[] = new String[numeroAmigos];
						//listaDeAmigos = friendsList.getFriendsIdsAsString();
						Vector<String> teste = friendsList.getFriendsIdsAsString();
						
						for(int i = 0; i < teste.size(); i++) {
							

							System.out.println(teste.get(i));
						}
						
						ListModel listaDeAmigosModel = new DefaultComboBoxModel(teste);
						listaDeAmigos = new JList();
						scrollPane.setViewportView(listaDeAmigos);
						listaDeAmigos.setModel(listaDeAmigosModel);
						listaDeAmigos.setBounds(184, 14, 155, 444);
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
					painelTabs.setBounds(89, 66, 261, 222);
					{
						jTabbedPane2 = new JTabbedPane();
						painelTabs.addTab("jTabbedPane2", null, jTabbedPane2, null);
					}
					{
						jTabbedPane1 = new JTabbedPane();
						painelTabs.addTab("jTabbedPane1", null, jTabbedPane1, null);
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

	@Override
	public void actionPerformed(ActionEvent arg0) {
		
		if(arg0.getSource() == menuItemSair) {
			System.exit(0);
		}
	}
}
