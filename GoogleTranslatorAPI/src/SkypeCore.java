import java.io.BufferedReader;
import java.io.InputStreamReader;

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
	
public class SkypeCore {
	
	private Chat chat = null;
	
	static {
		Connector.useJNIConnector(true);
	}

	public static void main(String[] args) throws Exception {
		
		SkypeCore core = new SkypeCore();
		core.connect();
		
		String text = "";
		String id = "";
		
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Enter a valid skype id to test the 1-1 messaging feature: ");
		id = br.readLine();
		System.out.print("> ");
		
		TranslateV2 v2 = new TranslateV2();
		
		GoogleAPI.setKey("AIzaSyCq1JQCESjgNTc4iM1tXMzEo9d2uVf3IP8");
		GoogleAPI.setHttpReferrer("http://code.google.com/p/google-api-translate-java");
		
		
		 
		//System.out.println(saida);
		
		while (true) {
			text = br.readLine();
			String saida = v2.execute(text, Language.PORTUGUESE, Language.ENGLISH);
			core.sendMessage(id, saida);
		}
		
		
	}
	
	private void sendMessage(String id, String text) throws SkypeException {
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
